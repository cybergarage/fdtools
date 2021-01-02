// Copyright (C) 2020 Satoshi Konno. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include <string.h>

#include <fdtools/dev/image.h>
#include <fdtools/img/error.h>

bool fdt_device_image_delete(FdtDeviceImage*);
bool fdt_device_image_open(FdtDeviceImage*, const char*, FdtFileMode, FdtError*);
bool fdt_device_image_close(FdtDeviceImage*, FdtError*);
bool fdt_device_image_isopened(FdtDeviceImage* img);
bool fdt_device_image_load(FdtDeviceImage*, FdtError*);
bool fdt_device_image_export(FdtDeviceImage*, FdtError*);
bool fdt_device_image_readsector(FdtDeviceImage*, FdtImageSector*, FdtError*);
bool fdt_device_image_writesector(FdtDeviceImage*, FdtImageSector*, FdtError*);

FdtImage* fdt_device_image_new(void)
{
  FdtDeviceImage* img = (FdtDeviceImage*)calloc(sizeof(FdtDeviceImage), 1);
  if (!img)
    return NULL;

  if (!fdt_image_init((FdtImage*)img)) {
    fdt_device_image_delete(img);
    return NULL;
  }

  img->dev = fdt_device_new();
  if (!img->dev) {
    fdt_device_image_delete(img);
    return NULL;
  }

  fdt_image_settype(img, FDT_IMAGE_TYPE_DEV);
  fdt_image_setopener(img, fdt_device_image_open);
  fdt_image_setcloser(img, fdt_device_image_close);
  fdt_image_setopenchecker(img, fdt_device_image_isopened);
  fdt_image_setdestructor(img, fdt_device_image_delete);
  fdt_image_setloader(img, fdt_device_image_load);
  fdt_image_setexporter(img, fdt_device_image_export);

  return (FdtImage*)img;
}

bool fdt_device_image_delete(FdtDeviceImage* img)
{
  if (!img)
    return false;

  if (!fdt_device_image_close(img, NULL))
    return false;

  if (!fdt_device_delete(img->dev))
    return false;
  img->dev = NULL;

  if (!fdt_image_clear((FdtImage*)img))
    return false;

  return true;
}

bool fdt_device_image_open(FdtDeviceImage* img, const char* name, FdtFileMode mode, FdtError* err)
{
  if (!img)
    return false;
  return fdt_device_open(img->dev, name, mode, err);
}

bool fdt_device_image_close(FdtDeviceImage* img, FdtError* err)
{
  if (!img)
    return false;
  return fdt_device_close(img->dev, err);
}

bool fdt_device_image_isopened(FdtDeviceImage* img)
{
  if (!img || !img->dev)
    return false;

  return fdt_device_isopened(img->dev);
}

bool fdt_image_setfloppyparams(FdtImage* img, FdtFloppyParams* fdparams, FdtError* err)
{
  if (!img || !fdparams)
    return false;
  fdt_image_setnumberofcylinder(img, fdt_floppy_params_gettrack(fdparams));
  fdt_image_setnumberofhead(img, fdt_floppy_params_gethead(fdparams));
  fdt_image_setnumberofsector(img, fdt_floppy_params_getsect(fdparams));
  fdt_image_setsectorsize(img, fdt_floppy_params_getssize(fdparams));
  return true;
}

bool fdt_device_image_load(FdtDeviceImage* img, FdtError* err)
{
  if (!img)
    return false;

  if (!fdt_device_image_isopened(img))
    return false;

  if (!fdt_device_image_generatesectors(img, err))
    return false;

  bool all_sector_status = true;
  for (FdtImageSector* sector = fdt_device_image_getsectors(img); sector; sector = fdt_image_sector_next(sector)) {
    if (!fdt_device_image_readsector(img, sector, err)) {
      fdt_error_setmessage(err, "Read error" FDT_IMAGE_MESSAGE_SECTOR_SIZE_PRINTF_FORMAT, fdt_image_sector_getcylindernumber(sector), fdt_image_sector_getheadnumber(sector), fdt_image_sector_getnumber(sector), fdt_image_sector_getsize(sector));
      all_sector_status = false;
    }
  }

  return all_sector_status;
}

bool fdt_device_image_readsector(FdtDeviceImage* img, FdtImageSector* sector, FdtError* err)
{
  if (!img || !sector)
    return false;

  off_t sector_offset = fdt_device_image_getsectoroffset(img, sector);
  if (sector_offset < 0)
    return false;

  size_t sector_size = fdt_image_getsectorsize(img);
  byte_t* sector_data = (byte_t*)malloc(sector_size);
  if (!sector_data)
    return false;

  if (!fdt_device_readoffsetblock(img->dev, sector_offset, sector_data, sector_size, err))
    return false;

  fdt_image_sector_setsize(sector, sector_size);
  fdt_image_sector_setdata(sector, sector_data);

  return true;
}

bool fdt_device_image_export(FdtDeviceImage* img, FdtError* err)
{
  if (!img)
    return false;

  if (!fdt_image_issectorssorted(img)) {
    if (!fdt_image_sortsectors(img)) {
      fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_SECTORS_NOT_SORTED, fdt_image_getname(img));
      return false;
    }
  }

  if (!fdt_device_image_isopened(img))
    return false;

  for (FdtImageSector* sector = fdt_device_image_getsectors(img); sector; sector = fdt_image_sector_next(sector)) {
    if (!fdt_device_image_writesector(img, sector, err))
      return false;
  }

  return true;
}

bool fdt_device_image_writesector(FdtDeviceImage* img, FdtImageSector* sector, FdtError* err)
{
  if (!img || !sector)
    return false;

  size_t sector_size = fdt_image_sector_getsize(sector);
  byte_t* sector_data = fdt_image_sector_getdata(sector);
  if ((sector_size <= 0) || !sector_data) {
    fdt_error_setmessage(err, "Bad sector " FDT_IMAGE_MESSAGE_SECTOR_SIZE_PRINTF_FORMAT, fdt_image_sector_getcylindernumber(sector), fdt_image_sector_getheadnumber(sector), fdt_image_sector_getnumber(sector), fdt_image_sector_getsize(sector));
    return false;
  }

  if (!fdt_device_writeblock(img->dev, sector_data, sector_size, err)) {
    fdt_error_appendmessage(err, FDT_IMAGE_MESSAGE_SECTOR_SIZE_PRINTF_FORMAT, fdt_image_sector_getcylindernumber(sector), fdt_image_sector_getheadnumber(sector), fdt_image_sector_getnumber(sector), fdt_image_sector_getsize(sector));
    return false;
  }

  return true;
}
