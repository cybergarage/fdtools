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

#include <fdtools/img/error.h>
#include <fdtools/img/image.h>

FdtImage* fdt_image_new()
{
  FdtImage* img = (FdtImage*)calloc(sizeof(FdtImage), 1);
  if (!img) {
    return NULL;
  }

  if (!fdt_image_init(img)) {
    fdt_image_delete(img);
    return NULL;
  }

  return img;
}

bool fdt_image_init(FdtImage* img)
{
  fdt_image_settype(img, FDT_IMAGE_TYPE_UNKNOWN);

  img->name = fdt_string_new();
  img->config = fdt_image_config_new();
  img->sectors = fdt_image_sectors_new();

  if (!img->config || !img->config) {
    return false;
  }

  return true;
}

bool fdt_image_delete(FdtImage* img)
{
  if (img->image_destructor)
    return img->image_destructor(img);
  free(img);
  return true;
}

bool fdt_image_clear(FdtImage* img)
{
  if (!img)
    return false;

  fdt_string_delete(img->name);
  fdt_image_config_delete(img->config);
  fdt_image_sectors_delete(img->sectors);

  return true;
}

bool fdt_image_open(FdtImage* img, const char* name, FdtFileMode mode, FdtError* err)
{
  if (!img)
    return false;
  return img->image_opener(img, name, mode, err);
}

bool fdt_image_close(FdtImage* img, FdtError* err)
{
  if (!img)
    return false;
  return img->image_closer(img, err);
}

bool fdt_image_load(FdtImage* img, FdtError* err)
{
  if (!img)
    return false;

  bool is_already_opened = img->image_openchcker(img);
  if (!is_already_opened) {
    if (!fdt_image_open(img, fdt_image_getname(img), FDT_FILE_READ, err))
      return false;
  }

  bool is_success = img->image_loader(img, err);

  if (!is_already_opened) {
    if (!fdt_image_close(img, err))
      return false;
  }

  return is_success;
}

bool fdt_image_import(FdtImage* img, FdtImage* src, FdtError* err)
{
  FdtImageConfig* src_config = fdt_image_config_copy(src->config);
  if (!src_config)
    return false;

  FdtImageSectors* src_sectors = fdt_image_sectors_copy(src->sectors, err);
  if (!src_sectors) {
    fdt_image_config_delete(src_config);
    return false;
  }

  fdt_image_config_delete(img->config);
  img->config = src_config;

  fdt_image_sectors_delete(img->sectors);
  img->sectors = src_sectors;

  return true;
}

bool fdt_image_importwithsorting(FdtImage* img, FdtImage* src, FdtError* err)
{
  if (!fdt_image_import(img, src, err))
    return false;

  if (!fdt_image_sortsectors(img)) {
    fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_SECTORS_NOT_SORTED, fdt_image_getname(img));
    return false;
  }

  return true;
}

bool fdt_image_export(FdtImage* img, FdtError* err)
{
  if (!img)
    return false;

  bool is_already_opened = img->image_openchcker(img);
  if (!is_already_opened) {
    if (!fdt_image_open(img, fdt_image_getname(img), FDT_FILE_WRITE, err))
      return false;
  }

  bool is_success = img->image_exporter(img, err);

  if (!is_already_opened) {
    if (!fdt_image_close(img, err))
      return false;
  }

  return is_success;
}

off_t fdt_image_getsectoroffset(FdtImage* img, FdtImageSector* sector)
{
  if (!img || !sector)
    return -1;

  if (!fdt_image_sector_isvalid(sector))
    return -1;

  size_t sector_size = fdt_image_getsectorsize(img);
  size_t number_of_head = fdt_image_getnumberofhead(img);
  size_t number_of_sector = fdt_image_getnumberofsector(img);
  size_t cylinder_no = fdt_image_sector_getcylindernumber(sector);
  size_t header_no = fdt_image_sector_getheadnumber(sector);
  size_t sector_no = fdt_image_sector_getnumber(sector) - 1; // Sector no stats from 1

  if ((cylinder_no < 0) || (cylinder_no < 0) || (sector_no < 0))
    return -1;

  size_t offset = (cylinder_no * number_of_head * number_of_sector) * sector_size;
  offset += (header_no * number_of_sector) * sector_size;
  offset += sector_no * sector_size;

  return offset;
}

bool fdt_image_isvalid(FdtImage* img, FdtError* err)
{
  if (!img)
    return false;

  FdtImageConfig* config = fdt_image_getconfig(img);
  if (!config)
    return false;

  if (!fdt_image_config_isvalid(config, err)) {
    return false;
  }

  size_t number_of_cylinder = fdt_image_config_getnumberofcylinder(config);
  size_t number_of_head = fdt_image_config_getnumberofhead(config);
  size_t number_of_sector = fdt_image_config_getnumberofsector(config);
  size_t config_sector_size = fdt_image_config_getsectorsize(config);

  for (size_t c = 0; c < number_of_cylinder; c++) {
    for (size_t h = 0; h < number_of_head; h++) {
      for (size_t s = 1; s <= number_of_sector; s++) {
        FdtImageSector* sector = fdt_image_getsector(img, c, h, s);
        if (!sector) {
          fdt_error_setmessage(err, "Not found sector " FDT_IMAGE_MESSAGE_SECTOR_PRINTF_FORMAT, c, h, s);
          return false;
        }
        if (!fdt_image_sector_hasdata(sector)) {
          fdt_error_setmessage(err, "No sector data " FDT_IMAGE_MESSAGE_SECTOR_PRINTF_FORMAT, c, h, s);
          return false;
        }
        size_t sector_size = fdt_image_sector_getsize(sector);
        if (sector_size != config_sector_size) {
          fdt_error_setmessage(err, "Invalid sector size " FDT_IMAGE_MESSAGE_SECTOR_PRINTF_FORMAT "%ld != %ld", c, h, s, sector_size, config_sector_size);
          return false;
        }
      }
    }
  }

  return true;
}

bool fdt_image_generatesectors(FdtImage* img, FdtError* err)
{
  if (!img)
    return false;

  if (!fdt_image_config_isvalid(img->config, err))
    return false;

  size_t number_of_cylinder = fdt_image_getnumberofcylinder(img);
  size_t number_of_head = fdt_image_getnumberofhead(img);
  size_t number_of_sector = fdt_image_getnumberofsector(img);
  size_t sector_size = fdt_image_getsectorsize(img);

  for (size_t c = 0; c < number_of_cylinder; c++) {
    for (size_t h = 0; h < number_of_head; h++) {
      for (size_t s = 1; s <= number_of_sector; s++) {
        FdtImageSector* sector = fdt_image_sector_new();
        if (!sector) {
          return false;
        }
        fdt_image_sector_setcylindernumber(sector, c);
        fdt_image_sector_setheadnumber(sector, h);
        fdt_image_sector_setnumber(sector, s);
        fdt_image_sector_setsize(sector, sector_size);
        fdt_image_addsector(img, sector);
      }
    }
  }

  return true;
}

bool fdt_image_equals(FdtImage* img, FdtImage* other, FdtError* err)
{
  if (!img || !other)
    return false;
  if (!fdt_image_config_equals(img->config, other->config, err))
    return false;
  if (!fdt_image_sectors_equals(img->sectors, other->sectors, err))
    return false;
  return true;
}

void fdt_image_print(FdtImage* img)
{
  if (img->config)
    fdt_image_config_print(img->config);
  if (img->sectors)
    fdt_image_sectors_print(img->sectors);
}
