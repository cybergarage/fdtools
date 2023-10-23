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
  fdu_program_usage(prg, ARG_IMAGE_FILENAME " " ARG_IMAGE_FILENAME " " ARG_IMAGE_DEVICE_CYL_HEAD_SEC);
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
  fdu_program_adddefaultoptions(prg);

  if (!fdu_program_parsearguments(prg, argc, argv, err)) {
    fdu_console_error(err);
    usage(prg);
    return EXIT_FAILURE;
  }

  if (fdt_program_getnarguments(prg) < 2) {
    usage(prg);
    return EXIT_FAILURE;
  }

  // Loads source file image

  const char* img_name_l = fdt_program_getargument(prg, 0);

  FdtImage* img_l = fdt_image_getimager(img_name_l, err);
  if (!img_l) {
    usage(prg);
    error(err);
  }
  if (!fdt_image_load(img_l, err)) {
    usage(prg);
    error(err);
  }

  const char* img_name_r = fdt_program_getargument(prg, 1);

  FdtImage* img_r = fdt_image_getimager(img_name_r, err);
  if (!img_r) {
    usage(prg);
    error(err);
  }
  if (!fdt_image_load(img_r, err)) {
    usage(prg);
    error(err);
  }

  // Sets command line options

  int cyclinder_start_no = 0;
  int cyclinder_end_no = fdt_image_getnumberofsector(img_l) - 1;
  if (3 <= fdt_program_getnarguments(prg)) {
    cyclinder_start_no = cyclinder_end_no = fdt_str2int(fdt_program_getargument(prg, 2));
  }

  int head_start_no = 0;
  int head_end_no = fdt_image_getnumberofhead(img_l) - 1;
  if (4 <= fdt_program_getnarguments(prg)) {
    head_start_no = head_end_no = fdt_str2int(fdt_program_getargument(prg, 3));
  }

  int sector_start_no = 1;
  int sector_end_no = fdt_image_getnumberofcylinder(img_l);
  if (5 <= fdt_program_getnarguments(prg)) {
    sector_start_no = sector_end_no = fdt_str2int(fdt_program_getargument(prg, 4));
  }

  // Dumps sector bytes

  for (int c = cyclinder_start_no; c <= cyclinder_end_no; c++) {
    for (int h = head_start_no; h <= head_end_no; h++) {
      for (int s = sector_start_no; s <= sector_end_no; s++) {
        printf("cyl:%d head:%d sect:%d\n", c, h, s);

        FdtImageSector* sector_l = fdt_image_getsector(img_l, c, h, s);
        if (!sector_l) {
          printf("X %s cyl:%d head:%d sect:%d\n", img_name_l, c, h, s);
          continue;
        }
        byte_t* sector_l_data = fdt_image_sector_getdata(sector_l);
        size_t sector_l_size = fdt_image_sector_getsize(sector_l);

        FdtImageSector* sector_r = fdt_image_getsector(img_r, c, h, s);
        if (!sector_r) {
          printf("X %s cyl:%d head:%d sect:%d\n", img_name_r, c, h, s);
          continue;
        }
        byte_t* sector_r_data = fdt_image_sector_getdata(sector_r);
        size_t sector_r_size = fdt_image_sector_getsize(sector_r);

        fdt_hexdump_compare_print(sector_l_data, sector_l_size, sector_r_data, sector_r_size);

        fdu_console_flush();
      }
    }
  }
  // Cleanups

  fdt_image_delete(img_l);
  fdt_image_delete(img_r);

  fdu_console_flush();
  fdt_program_delete(prg);
  fdt_error_delete(err);

  return 0;
}