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
#include <fdutils/device.h>
#include <fdutils/program.h>

void usage(FdtProgram* prg)
{
  fdu_program_usage(prg, "<source device or file name> <destination device or file name>");
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
  fdu_program_adddeviceoptions(prg);

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

  const char* src_img_name = fdt_program_getargument(prg, 0);
  FdtImage* src_img = fdt_image_getimager(src_img_name, err);
  if (!src_img) {
    error(err);
  }

  if (fdt_image_isdevice(src_img)) {
    if (!fdu_device_image_setoptions(src_img, prg, err)) {
      error(err);
    }
    if (!fdu_device_image_load(src_img, err)) {
      error(err);
    }
  }
  else {
    if (!fdt_image_load(src_img, err)) {
      error(err);
    }
  }

  // Print line field to message buffer

  fdu_console_lf();

  // Imports source file image to dest file image

  const char* dst_img_name = fdt_program_getargument(prg, 1);
  FdtImage* dst_img = fdt_image_getimager(dst_img_name, err);
  if (!dst_img) {
    error(err);
  }
  if (!fdt_image_import(dst_img, src_img, err)) {
    error(err);
  }

  // Delete imported source image

  fdt_image_delete(src_img);

  // Exports source file image to dest file image

  if (fdt_image_isdevice(dst_img)) {
    if (!fdu_device_image_export(dst_img, err)) {
      error(err);
    }
  }
  else {
    if (!fdt_image_export(dst_img, err)) {
      error(err);
    }
  }

  fdt_image_delete(dst_img);

  // Cleanups

  fdu_console_flush();
  fdt_program_delete(prg);
  fdt_error_delete(err);

  return 0;
}