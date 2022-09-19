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
#include <fdtools/util/hexdump.h>
#include <fdtools/util/log.h>
#include <fdtools/util/program.h>
#include <fdtools/util/string.h>

#include <fdutils/console.h>
#include <fdutils/device.h>
#include <fdutils/program.h>

void usage(FdtProgram* prg)
{
  fdu_program_usage(prg, ARG_IMAGE_DEVICE_FILENAME);
}

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
  fdu_program_adddeviceoptions(prg);

  if (!fdu_program_parse_arguments(prg, argc, argv, err)) {
    fdu_console_error(err);
    usage(prg);
    return EXIT_FAILURE;
  }

  if (fdt_program_getnarguments(prg) < 1) {
    usage(prg);
    return EXIT_FAILURE;
  }

  // Loads source file image

  const char* img_name = fdt_program_getargument(prg, 0);

  FdtImage* img = fdt_image_plugins_create(img_name, err);
  if (!img) {
    exit_error(err);
  }

  if (fdt_image_isdevice(img)) {
    if (!fdu_image_setdeviceoptions(img, prg, err)) {
      exit_error(err);
    }
  }

  if (fdt_image_isdevice(img)) {
    // Shows progress infomation for device image types
    // TODO: Sets image parameters to device
    FdtDeviceImage* dev_img = (FdtDeviceImage*)img;
    if (!fdt_device_image_open(dev_img, img_name, FDT_FILE_READ, err)) {
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
    if (!fdt_image_load(img, err)) {
      exit_error(err);
    }
  }

  // Print line field to message buffer

  fdu_console_lf();

  // Sets command line options

  int cyclinder_start_no = 0;
  int cyclinder_end_no = fdt_image_getnumberofsector(img) - 1;
  if (2 <= fdt_program_getnarguments(prg)) {
    cyclinder_start_no = cyclinder_end_no = fdt_str2int(fdt_program_getargument(prg, 1));
  }

  int head_start_no = 0;
  int head_end_no = fdt_image_getnumberofhead(img) - 1;
  if (3 <= fdt_program_getnarguments(prg)) {
    head_start_no = head_end_no = fdt_str2int(fdt_program_getargument(prg, 2));
  }

  int sector_start_no = 1;
  int sector_end_no = fdt_image_getnumberofcylinder(img);
  if (4 <= fdt_program_getnarguments(prg)) {
    sector_start_no = sector_end_no = fdt_str2int(fdt_program_getargument(prg, 3));
  }

  // Dumps sector bytes

  for (int c = cyclinder_start_no; c <= cyclinder_end_no; c++) {
    for (int h = head_start_no; h <= head_end_no; h++) {
      for (int s = sector_start_no; s <= sector_end_no; s++) {
        FdtImageSector* sector = fdt_image_getsector(img, c, h, s);
        if (!sector)
          continue;
        printf("cyl:%d head:%d sect:%d\n", c, h, s);
        size_t sector_size = fdt_image_sector_getsize(sector);
        byte_t* sector_data = fdt_image_sector_getdata(sector);
        fdt_hexdump_print(sector_data, sector_size);
        fdu_console_flush();
      }
    }
  }
  // Cleanups

  fdt_image_delete(img);
  fdu_console_flush();
  fdt_program_delete(prg);
  fdt_error_delete(err);

  return 0;
}