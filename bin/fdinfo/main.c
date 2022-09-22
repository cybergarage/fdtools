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

#include <fdtools/dev/image.h>
#include <fdtools/img/image.h>
#include <fdtools/plugins/image.h>
#include <fdtools/util/log.h>
#include <fdtools/util/program.h>

#include <fdutils/console.h>
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
  fdu_program_adddefaultoptions(prg);

  if (!fdu_program_parsearguments(prg, argc, argv, err)) {
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
  FdtImage* img = fdt_image_plugins_createimagebyfile(img_name, err);
  if (!img) {
    error(err);
  }

  FdtImageType img_type = fdt_image_gettype(img);

  switch (img_type) {
  case FDT_IMAGE_TYPE_DEV: {
    // Gets current device parameters, and sets the parameters to image.
    FdtDevice* dev = fdt_device_new();
    fdt_device_setname(dev, img_name);
    if (!fdt_device_open(dev, FDT_FILE_READ, err)) {
      error(err);
    }

    FdtFloppyParams* fdparams = fdt_floppy_params_new();
    if (!dev || !fdparams) {
      panic();
    }

    // Checks the floppy format when a floppy disk is inserted in the device.
    if (!fdt_device_detectfloppyformat(dev, fdparams, err)) {
      // The device has no floppy disk, and so gets only current floppy settings.
      if (!fdt_device_getfloppyparameters(dev, fdparams, err)) {
        error(err);
      }
    }
    fdu_console_message("%s", fdt_floppy_params_getdescription(fdparams));

    fdt_floppy_params_delete(fdparams);
    if (!fdt_device_close(dev, err)) {
      error(err);
    }
    fdt_device_delete(dev);
  } break;
  default: {
    if (!fdt_image_load(img, err)) {
      error(err);
    }
    const char* type = fdt_image_gettypeid(img);
    size_t cyl = fdt_image_getnumberofcylinder(img);
    size_t head = fdt_image_getnumberofhead(img);
    size_t sec = fdt_image_getnumberofsector(img);
    size_t ssize = fdt_image_getsectorsize(img);
    fdu_console_message("type=%s cyl=%ld, head=%ld, sect=%ld, ssize=%ld", type, cyl, head, sec, ssize);
  }
  }

  // Cleanups

  fdt_image_delete(img);
  fdt_error_delete(err);

  return 0;
}