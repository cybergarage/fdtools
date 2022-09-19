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

#include <fdtools/dev/device.h>
#include <fdtools/dev/image.h>
#include <fdtools/img/image.h>
#include <fdtools/util/program.h>

#include "device.h"
#include "program.h"

void fdu_program_adddeviceoptions(FdtProgram* prg)
{
  fdt_program_addoption(prg, OPT_CYLINDERS, "number of cylinders", true, "");
  fdt_program_addoption(prg, OPT_HEADS, "number of heads", true, "");
  fdt_program_addoption(prg, OPT_SECTORS, "number of sectors", true, "");
  fdt_program_addoption(prg, OPT_SSIZE, "sector size", true, "");
  fdt_program_addoption(prg, OPT_RETRY_PASSES, "number of retry passes", false, "");
}

bool fdu_image_setdeviceoptions(FdtImage* img, FdtProgram* prg, FdtError* err)
{
  FdtDevice* dev = fdt_device_new();
  FdtFloppyParams* fdparams = fdt_floppy_params_new();
  if (!dev || !fdparams) {
    panic();
  }
  if (!fdt_device_getfloppyparameters(dev, fdparams, err)) {
    return false;
  }
  if (!fdt_device_image_setfloppyparams(img, fdparams, err)) {
    return false;
  }
  fdt_device_delete(dev);
  fdt_floppy_params_delete(fdparams);

  return true;
}
