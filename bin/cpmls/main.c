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
#include <fdtools/util/program.h>
#include <fdtools/util/string.h>

#include <fdutils/console.h>
#include <fdutils/floppy.h>
#include <fdutils/program.h>

int main(int argc, char* argv[])
{
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

  if (fdt_program_getnarguments(prg) < 1) {
    fdu_program_usage(prg);
    return EXIT_FAILURE;
  }

  // Loads the spcefied file image

  const char* img_name = fdt_program_getargument(prg, 0);

  FdtImage* img = fdt_image_plugins_create(img_name, err);
  if (!img) {
    exit_error(err);
  }

  if (!fdt_image_load(img, err)) {
    exit_error(err);
  }

  // Cleanups

  fdt_image_delete(img);
  fdu_console_flush();
  fdt_program_delete(prg);
  fdt_error_delete(err);

  return 0;
}