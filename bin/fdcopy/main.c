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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <fdtools/dev/device.h>
#include <fdtools/dev/image.h>
#include <fdtools/img/image.h>
#include <fdtools/plugins/image.h>
#include <fdtools/util/log.h>
#include <fdtools/util/program.h>
#include <fdtools/util/string.h>

#include <fdutils/console.h>
#include <fdutils/floppy.h>
#include <fdutils/program.h>

int main(int argc, char* argv[])
{
  fdu_console_enabled();

  FdtError* err = fdt_error_new();
  if (!err) {
    panic();
  }

  // Parses command line arguments

  FdtProgram* prg = fdt_program_new();
  if (!prg) {
    panic();
  }
  fdu_program_add_default_options(prg);
  fdu_program_add_floppy_options(prg);

  if (!fdu_program_parse_arguments(prg, argc, argv, err)) {
    fdu_console_error(err);
    fdu_program_usage(prg);
    return EXIT_FAILURE;
  }

  if (fdt_program_getnarguments(prg) < 2) {
    fdu_program_usage(prg);
    return EXIT_FAILURE;
  }

  // Loads source file image

  const char* src_img_name = fdt_program_getargument(prg, 0);
  FdtImage* src_img = fdt_image_plugins_create(src_img_name, err);
  if (!src_img) {
    exit_error(err);
  }

  if (fdt_image_isdevice(src_img)) {
    // Gets current device parameters, and set the parameters to image.
    FdtDevice* dev = fdt_device_new();
    fdt_device_setname(dev, src_img_name);
    FdtFloppyParams* fdparams = fdt_floppy_params_new();
    if (!dev || !fdparams) {
      panic();
    }
    if (!fdt_device_getfloppyparameters(dev, fdparams, err)) {
      exit_error(err);
    }
    if (!fdt_device_image_setfloppyparams(src_img, fdparams, err)) {
      exit_error(err);
    }
    fdt_device_delete(dev);
    fdt_floppy_params_delete(fdparams);
  }

  if (fdt_image_isdevice(src_img)) {
    // Shows progress infomation for device image types
    // TODO: Sets image parameters to device
    FdtDeviceImage* dev_img = (FdtDeviceImage*)src_img;
    if (!fdt_device_image_open(dev_img, src_img_name, FDT_FILE_READ, err)) {
      exit_error(err);
    }
    if (!fdt_device_image_generatesectors(dev_img, err)) {
      exit_error(err);
    }
    size_t dev_sector_cnt = fdt_device_image_getnsectors(dev_img);
    size_t dev_read_sector_cnt = 0;
    fdu_console_refresh_progresstime();
    FdtImageSector* sector = fdt_device_image_geterrorsector(dev_img);
    FdtImageSector* last_sector;
    while (sector) {
      last_sector = sector;
      fdu_console_printdeviceprogress(dev_img, sector, dev_read_sector_cnt, dev_sector_cnt);
      if (fdt_device_image_readsector(dev_img, sector, err)) {
        dev_read_sector_cnt++;
      }
      sector = fdt_device_image_geterrorsector(dev_img);
    }
    if (last_sector) {
      fdu_console_printdeviceprogress(dev_img, last_sector, dev_read_sector_cnt, dev_sector_cnt);
    }
    if (!fdt_device_image_close(dev_img, err)) {
      exit_error(err);
    }
  }
  else {
    if (!fdt_image_load(src_img, err)) {
      exit_error(err);
    }
  }

  // Print line field to message buffer

  fdu_console_lf();

  // Imports source file image to dest file image

  const char* dst_img_name = fdt_program_getargument(prg, 1);
  FdtImage* dst_img = fdt_image_plugins_create(dst_img_name, err);
  if (!dst_img) {
    exit_error(err);
  }
  if (!fdt_image_import(dst_img, src_img, err)) {
    exit_error(err);
  }

  // Delete imported source image

  fdt_image_delete(src_img);

  // Exports source file image to dest file image

  if (fdt_image_isdevice(dst_img)) {
    // Shows progress infomation for device image types
    FdtDeviceImage* dev_img = (FdtDeviceImage*)dst_img;
    if (!fdt_device_image_open(dev_img, dst_img_name, FDT_FILE_WRITE, err)) {
      exit_error(err);
    }
    size_t dev_sector_cnt = fdt_device_image_getnsectors(dev_img);
    size_t dev_wrote_sector_cnt = 0;
    fdu_console_refresh_progresstime();
    FdtImageSector* last_sector;
    for (FdtImageSector* sector = fdt_device_image_getsectors(dev_img); sector; sector = fdt_image_sector_next(sector)) {
      last_sector = sector;
      fdu_console_printdeviceprogress(dev_img, sector, dev_wrote_sector_cnt, dev_sector_cnt);
      if (fdt_device_image_writesector(dev_img, sector, err)) {
        dev_wrote_sector_cnt++;
      }
      else {
        exit_error(err);
      }
    }
    if (last_sector) {
      fdu_console_printdeviceprogress(dev_img, last_sector, dev_wrote_sector_cnt, dev_sector_cnt);
    }
    if (!fdt_device_image_close(dev_img, err)) {
      exit_error(err);
    }
  }
  else {
    if (!fdt_image_export(dst_img, err)) {
      exit_error(err);
    }
  }

  fdt_image_delete(dst_img);

  // Cleanups

  fdu_console_flush();
  fdt_program_delete(prg);
  fdt_error_delete(err);

  return 0;
}