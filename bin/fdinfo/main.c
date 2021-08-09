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
#include <fdtools/util/program.h>

const char* OPT_VERBOSE = "v";
const char* OPT_DEBUG = "d";

bool verbose_enabled = false;
bool debug_enabled = false;

void print_usage(FdtProgram* prg)
{
  printf("Usage: %s [OPTIONS] <device or file name> \n", fdt_program_getname(prg));
  fdt_program_printoptionusages(prg);
}

void print_message(const char* format, ...)
{
  char msg[512];
  va_list list;
  va_start(list, format);
  vsnprintf(msg, sizeof(msg), format, list);
  va_end(list);
  printf("%s\n", msg);

  fflush(stdout);
}

void print_error(FdtError* err)
{
  printf("%s\n", debug_enabled ? fdt_error_getdebugmessage(err) : fdt_error_getmessage(err));
  fflush(stdout);
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
  fdt_program_addoption(prg, OPT_VERBOSE, "enable verbose messages", false, "");

  if (!fdt_program_parse(prg, argc, argv, err)) {
    print_error(err);
    print_usage(prg);
    return EXIT_FAILURE;
  }

  if (fdt_program_getnarguments(prg) < 1) {
    print_usage(prg);
    return EXIT_FAILURE;
  }

  // Sets command line options

  if (fdt_program_isoptionenabled(prg, OPT_VERBOSE)) {
    verbose_enabled = true;
  }
  if (fdt_program_isoptionenabled(prg, OPT_DEBUG)) {
    debug_enabled = true;
  }

  // Loads source file image

  const char* img_name = fdt_program_getargument(prg, 0);
  FdtImage* img = fdt_image_name_new(img_name, err);
  if (!img) {
    exit_error(err);
  }

  FdtImageType img_type = fdt_image_gettype(img);

  switch (img_type) {
  case FDT_IMAGE_TYPE_DEV: {
    // Gets current device parameters, and set the parameters to image.
    FdtDevice* dev = fdt_device_new();
    fdt_device_setname(dev, img_name);
    FdtFloppyParams* fdparams = fdt_floppy_params_new();
    if (!dev || !fdparams) {
      panic();
    }
    if (!fdt_device_getfloppyparameters(dev, fdparams, err)) {
      exit_error(err);
    }
    print_message("%s", fdt_floppy_params_getdescription(fdparams));
    if (!fdt_device_image_setfloppyparams(img, fdparams, err)) {
      exit_error(err);
    }
    fdt_device_delete(dev);
    fdt_floppy_params_delete(fdparams);
  } break;
  default: {
    if (!fdt_image_load(img, err)) {
      exit_error(err);
    }
    const char* type = fdt_image_gettypestring(img);
    size_t cyl = fdt_image_getnumberofcylinder(img);
    size_t head = fdt_image_getnumberofhead(img);
    size_t sec = fdt_image_getnumberofsector(img);
    size_t ssize = fdt_image_getsectorsize(img);
    print_message("type=%s cyl=%ld, head=%ld, sect=%ld, ssize=%ld", type, cyl, head, sec, ssize);
  }
  }

  // Prints image parameters

  // Cleanups

  fdt_image_delete(img);
  fdt_error_delete(err);

  return 0;
}