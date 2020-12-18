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

#if defined(__linux__)

#include <fcntl.h>

#include <linux/fd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fdtools/error.h>

#include <fdtools/dev/device.h>

bool fdt_device_getfloppyparams(floppy_struct* fdprms, FdtFloppyParams* params, FdtError* err);

bool fdt_device_getparameters(FdtDevice* dev, FdtError* err)
{
  if (dev->fd < 0)
    return false;

  struct floppy_struct fdprms;
  if (ioctl(dev->fd, FDGETPRM, &fdprms) < 0) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  return true;
}

bool fdt_device_getfloppyparams(floppy_struct* fdprms, FdtFloppyParams* params, FdtError* err)
{
  if (!fdprms || !params)
    return false;

  fdt_floppy_params_setsize(params, fdprms->size);
  fdt_floppy_params_setsect(params, fdprms->sect);
  fdt_floppy_params_setsize(params, fdprms->head);
  fdt_floppy_params_setsize(params, fdprms->track);
  fdt_floppy_params_setsize(params, fdprms->stretch);
  fdt_floppy_params_setsize(params, fdprms->gap);
  fdt_floppy_params_setsize(params, fdprms->rate);
  fdt_floppy_params_setsize(params, fdprms->spec1);
  fdt_floppy_params_setsize(params, fdprms->fmt_gap);

  return true;
}

bool fdt_device_setparameters(FdtDevice* dev, FdtError* err)
{
  if (dev->fd < 0)
    return false;

  struct floppy_struct fdprms;
  if (ioctl(dev->fd, FDSETPRM, &fdprms) < 0) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  return true;
}

#endif
