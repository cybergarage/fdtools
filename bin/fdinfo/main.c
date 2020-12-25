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

int main(int argc, char* argv[])
{
  const char* dev_name = "/dev/fd0";
  if (1 < argc) {
    dev_name = argv[1];
  }

  FdtDevice* dev = fdt_device_new();
  if (!dev)
    return 1;

  FdtError* err = fdt_error_new();
  if (!err)
    return 1;

  FdtFloppyParams* fdparams = fdt_floppy_params_new();
  if (!fdparams)
    return 1;

  if (fdt_device_open(dev, dev_name, FDT_DEVICE_READ, err)) {
    if (fdt_device_getfloppyparameters(dev, fdparams, err)) {
      printf("device  : %s\n", dev_name);
      printf("size    : %ld\n", fdt_floppy_params_getsize(fdparams));
      printf("head    : %ld\n", fdt_floppy_params_gethead(fdparams));
      printf("track   : %ld\n", fdt_floppy_params_gettrack(fdparams));
      printf("sector  : %ld\n", fdt_floppy_params_getsectorsize(fdparams));
      printf("stretch : %ld\n", fdt_floppy_params_getstretch(fdparams));
      printf("gap     : %02X\n", fdt_floppy_params_getgap(fdparams));
      printf("rate    : %02X\n", fdt_floppy_params_getrate(fdparams));
      printf("spec1   : %02X\n", fdt_floppy_params_getspec1(fdparams));
      printf("fmt gap : %02X\n", fdt_floppy_params_getfmtgap(fdparams));
    }
    else {
      printf("%s\n", fdt_error_getdebugmessage(err));
    }
  }
  else {
    printf("%s\n", fdt_error_getdebugmessage(err));
  }

  fdt_device_delete(dev);
  fdt_floppy_params_delete(fdparams);
  fdt_error_delete(err);

  return 0;
}