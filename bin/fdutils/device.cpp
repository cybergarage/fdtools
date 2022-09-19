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

#include <fdtools/dev/device.h>
#include <fdtools/dev/image.h>
#include <fdtools/img/image.h>
#include <fdtools/util/program.h>

#include "console.h"
#include "device.h"
#include "program.h"

void fdu_program_adddeviceoptions(FdtProgram* prg)
{
  fdt_program_addoption(prg, OPT_CYLINDERS, "number of cylinders", true, "");
  fdt_program_addoption(prg, OPT_HEADS, "number of heads", true, "");
  fdt_program_addoption(prg, OPT_SECTORS, "number of sectors", true, "");
  fdt_program_addoption(prg, OPT_SSIZE, "sector size", true, "");
  fdt_program_addoption(prg, OPT_RETRY_PASSES, "number of retry passes", false, "");
}

bool fdu_device_image_setoptions(FdtImage* img, FdtProgram* prg, FdtError* err)
{
  // TODO: Sets image parameters to device
  FdtDevice* dev = fdt_device_new();
  FdtFloppyParams* fdparams = fdt_floppy_params_new();
  if (!dev || !fdparams) {
    panic();
  }
  if (!fdt_device_getfloppyparameters(dev, fdparams, err)) {
    return false;
  }
  if (!fdt_device_image_setfloppyparams(img, fdparams, err)) {
    return false;
  }
  fdt_device_delete(dev);
  fdt_floppy_params_delete(fdparams);

  return true;
}

bool fdu_device_image_load(FdtImage* img, FdtError* err)
{
  const char* dev_name = fdt_image_gettarget(img);
  FdtDeviceImage* dev_img = (FdtDeviceImage*)img;
  if (!fdt_device_image_open(dev_img, dev_name, FDT_FILE_READ, err)) {
    return false;
  }
  if (!fdt_device_image_generatesectors(dev_img, err)) {
    return false;
  }

  fdu_console_refresh_progresstime();

  size_t dev_sector_cnt = fdt_device_image_getnsectors(dev_img);
  size_t dev_read_sector_cnt = 0;
  FdtImageSector* sector = fdt_device_image_geterrorsector(dev_img);
  FdtImageSector* last_sector;
  while (sector) {
    last_sector = sector;
    fdu_console_updatedeviceprogress(dev_img, sector, dev_read_sector_cnt, dev_sector_cnt);
    if (fdt_device_image_readsector(dev_img, sector, err)) {
      dev_read_sector_cnt++;
    }
    sector = fdt_device_image_geterrorsector(dev_img);
  }
  if (last_sector) {
    fdu_console_updatedeviceprogress(dev_img, last_sector, dev_read_sector_cnt, dev_sector_cnt);
  }
  if (!fdt_device_image_close(dev_img, err)) {
    return false;
  }
  return true;
}

bool fdu_device_image_export(FdtImage* img, FdtError* err)
{
  const char* dev_name = fdt_image_gettarget(img);
  FdtDeviceImage* dev_img = (FdtDeviceImage*)img;
  if (!fdt_device_image_open(dev_img, dev_name, FDT_FILE_WRITE, err)) {
    return false;
  }
  size_t dev_sector_cnt = fdt_device_image_getnsectors(dev_img);
  size_t dev_wrote_sector_cnt = 0;
  fdu_console_refresh_progresstime();
  FdtImageSector* last_sector;
  for (FdtImageSector* sector = fdt_device_image_getsectors(dev_img); sector; sector = fdt_image_sector_next(sector)) {
    last_sector = sector;
    fdu_console_updatedeviceprogress(dev_img, sector, dev_wrote_sector_cnt, dev_sector_cnt);
    if (fdt_device_image_writesector(dev_img, sector, err)) {
      dev_wrote_sector_cnt++;
    }
    else {
      return false;
    }
  }
  if (last_sector) {
    fdu_console_updatedeviceprogress(dev_img, last_sector, dev_wrote_sector_cnt, dev_sector_cnt);
  }
  if (!fdt_device_image_close(dev_img, err)) {
    return false;
  }
  return true;
}
