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
#include <stdlib.h>

#include <fdtools/dev/device.h>
#include <fdtools/img/image.h>
#include <fdtools/util/program.h>

void print_usage(FdtProgram* prg)
{
  printf("Usage: %s [OPTIONS] <source file name> <destination file name>\n", fdt_program_getname(prg));
  fdt_program_printoptionusages(prg);
}

void print_error(FdtError* err)
{
  printf("Error: %s\n", fdt_error_getmessage(err));
}

void exit_systemerror()
{
  exit(EXIT_FAILURE);
}

void exit_error(FdtError* err)
{
  print_error(err);
  exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
  FdtError* err = fdt_error_new();
  if (!err) {
    exit_systemerror();
  }

  FdtProgram* prg = fdt_program_new();
  if (!prg) {
    exit_systemerror();
  }
  fdt_program_addoption(prg, "c", "number of cylinders", true, "");
  fdt_program_addoption(prg, "h", "number of heads", true, "");
  fdt_program_addoption(prg, "n", "number of sectors", true, "");
  fdt_program_addoption(prg, "s", "sector size", true, "");
  fdt_program_addoption(prg, "v", "enable verbose messages", false, "");

  if (!fdt_program_parse(prg, argc, argv, err)) {
    print_error(err);
    print_usage(prg);
    return EXIT_FAILURE;
  }

  if (fdt_program_getnarguments(prg) < 2) {
    print_usage(prg);
    return EXIT_FAILURE;
  }

  // Load source file image

  const char* src_img_name = fdt_program_getargument(prg, 0);
  FdtImage* src_img = fdt_image_name_new(src_img_name, err);
  if (!src_img) {
    exit_error(err);
  }
  switch (fdt_image_gettype(src_img)) {
  case FDT_IMAGE_TYPE_DEV: {
    // Gets current device parameters, and set the parameters to image.
    FdtDevice* dev = fdt_device_new();
    FdtFloppyParams* fdparams = fdt_floppy_params_new();
    if (!dev || !fdparams) {
      exit_systemerror();
    }
    if (fdt_device_open(dev, src_img_name, FDT_FILE_READ, err)) {
      exit_error(err);
    }
    if (fdt_device_getfloppyparameters(dev, fdparams, err)) {
      exit_error(err);
    }
    fdt_image_setnumberofcylinder(src_img, fdt_floppy_params_gettrack(fdparams));
    fdt_image_setnumberofhead(src_img, fdt_floppy_params_gethead(fdparams));
    fdt_image_setnumberofsector(src_img, fdt_floppy_params_getsect(fdparams));
    fdt_image_setsectorsize(src_img, fdt_floppy_params_getsectorsize(fdparams));
    fdt_device_delete(dev);
    fdt_floppy_params_delete(fdparams);
  } break;
  case FDT_IMAGE_TYPE_RAW:
    // TODO: Set parameters
    break;
  }

  if (!fdt_image_open(src_img, src_img_name, FDT_FILE_READ, err)) {
    exit_error(err);
  }
  if (!fdt_image_load(src_img, err)) {
    exit_error(err);
  }
  if (!fdt_image_close(src_img, err)) {
    exit_error(err);
  }

  // Export source file image

  const char* dst_img_name = fdt_program_getargument(prg, 1);
  FdtImage* dst_img = fdt_image_name_new(dst_img_name, err);
  if (!dst_img) {
    exit_error(err);
  }
  if (!fdt_image_import(dst_img, src_img, err)) {
    exit_error(err);
  }
  fdt_image_delete(src_img);

  if (!fdt_image_open(dst_img, src_img_name, FDT_FILE_WRITE, err)) {
    exit_error(err);
  }
  if (!fdt_image_export(dst_img, err)) {
    exit_error(err);
  }
  if (!fdt_image_close(dst_img, err)) {
    exit_error(err);
  }
  fdt_image_delete(dst_img);

  // Cleanup

  fdt_program_delete(prg);
  fdt_error_delete(err);

  return 0;
}