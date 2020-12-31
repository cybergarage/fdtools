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

#include <fdtools/dev/device.h>
#include <fdtools/dev/image.h>
#include <fdtools/img/image.h>
#include <fdtools/util/program.h>

void print_message(const char* format, ...)
{
  char msg[512];
  va_list list;
  va_start(list, format);
  vsnprintf(msg, sizeof(msg), format, list);
  va_end(list);
  printf("%s\n", msg);
}

void print_usage(FdtProgram* prg)
{
  printf("Usage: %s [OPTIONS] <source file name> <destination file name>\n", fdt_program_getname(prg));
  fdt_program_printoptionusages(prg);
}

void print_error(FdtError* err)
{
  printf("Error: %s\n", fdt_error_getmessage(err));
}

void panic()
{
  exit(EXIT_FAILURE);
}

void exit_error(FdtError* err)
{
  print_error(err);
  exit(EXIT_FAILURE);
}

void print_progress(FdtImageSector* sector, size_t dev_read_sector_cnt, size_t dev_sector_cnt)
{
  int read_per = (dev_sector_cnt * 100) / dev_read_sector_cnt;
  printf("\rT:%03ld:%03ld H:%ld (%d%%)", fdt_image_sector_getcylindernumber(sector), fdt_image_sector_getnumber(sector), fdt_image_sector_getheadnumber(sector), read_per);
}

int main(int argc, char* argv[])
{
  FdtError* err = fdt_error_new();
  if (!err) {
    panic();
  }

  FdtProgram* prg = fdt_program_new();
  if (!prg) {
    panic();
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

  FdtImageType src_img_type = fdt_image_gettype(src_img);

  switch (src_img_type) {
  case FDT_IMAGE_TYPE_DEV: {
    // Gets current device parameters, and set the parameters to image.
    FdtDevice* dev = fdt_device_new();
    FdtFloppyParams* fdparams = fdt_floppy_params_new();
    if (!dev || !fdparams) {
      panic();
    }
    if (!fdt_device_open(dev, src_img_name, FDT_FILE_READ, err)) {
      exit_error(err);
    }
    if (!fdt_device_getfloppyparameters(dev, fdparams, err)) {
      exit_error(err);
    }
    fdt_image_setnumberofcylinder(src_img, fdt_floppy_params_gettrack(fdparams));
    fdt_image_setnumberofhead(src_img, fdt_floppy_params_gethead(fdparams));
    fdt_image_setnumberofsector(src_img, fdt_floppy_params_getsect(fdparams));
    fdt_image_setsectorsize(src_img, fdt_floppy_params_getssize(fdparams));
    fdt_device_delete(dev);
    fdt_floppy_params_delete(fdparams);

    print_message("cyl=%ld head=%ld sect=%ld ssize=%ld\n", fdt_image_getnumberofcylinder(src_img), fdt_image_getnumberofhead(src_img), fdt_image_getnumberofsector(src_img), fdt_image_getsectorsize(src_img));
  } break;
  case FDT_IMAGE_TYPE_RAW:
    // TODO: Set parameters
    break;
  }

  switch (src_img_type) {
  // Shows progress infomation for device image types
  case FDT_IMAGE_TYPE_DEV: {
    FdtDeviceImage* dev_img = (FdtDeviceImage*)src_img;
    if (!fdt_device_image_open(dev_img, src_img_name, FDT_FILE_READ, err)) {
      exit_error(err);
    }
    if (!fdt_device_image_generatesectors(dev_img, err)) {
      exit_error(err);
    }
    size_t dev_sector_cnt = fdt_device_image_getnsectors(dev_img);
    size_t dev_read_sector_cnt = 0;
    FdtImageSector* sector = fdt_device_image_geterrorsector(dev_img);
    FdtImageSector* last_sector;
    while (sector) {
      last_sector = sector;
      print_progress(sector, dev_read_sector_cnt, dev_sector_cnt);
      if (fdt_device_image_readsector(dev_img, sector, err)) {
        dev_read_sector_cnt++;
      }
      sector = fdt_device_image_geterrorsector(dev_img);
    }
    if (last_sector) {
      print_progress(last_sector, dev_read_sector_cnt, dev_sector_cnt);
    }
    if (!fdt_device_image_close(dev_img, err)) {
      exit_error(err);
    }
  } break;
  default: {
    if (!fdt_image_load(src_img, err)) {
      exit_error(err);
    }
  }
  }

  // Export source file image

  const char* dst_img_name = fdt_program_getargument(prg, 1);
  print_message("exporting %s ....", dst_img_name);
  FdtImage* dst_img = fdt_image_name_new(dst_img_name, err);
  if (!dst_img) {
    exit_error(err);
  }
  print_message("importing %s ....", dst_img_name);
  if (!fdt_image_import(dst_img, src_img, err)) {
    exit_error(err);
  }
  print_message("imported");

  fdt_image_delete(src_img);

  print_message("exporting .....");
  if (!fdt_image_export(dst_img, err)) {
    exit_error(err);
  }
  print_message("exported");

  fdt_image_delete(dst_img);

  // Cleanup

  fdt_program_delete(prg);
  fdt_error_delete(err);

  return 0;
}