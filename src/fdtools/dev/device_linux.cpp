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

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#include <fdtools/error.h>

#include <fdtools/dev/device.h>
#include <fdtools/dev/floppy.h>

bool fdt_device_setparameters(FdtDevice* dev, FdtError* err)
{
  if (!dev)
    return false;

  int fd = fdt_device_getfileno(dev);
  if (fd == -1)
    return false;

  struct floppy_struct fdprms;
  if (ioctl(fd, FDSETPRM, &fdprms) < 0) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  return true;
}

bool fdt_device_getfloppyparameters(FdtDevice* dev, FdtFloppyParams* params, FdtError* err)
{
  if (!dev)
    return false;

  bool is_already_opened = fdt_device_isopened(dev);
  if (!is_already_opened) {
    if (!fdt_device_open(dev, fdt_device_getname(dev), FDT_FILE_READ, err)) {
      return false;
    }
  }

  int fd = fdt_device_getfileno(dev);
  if (fd == -1)
    return false;

  // Check fstat parameters

  struct stat stat;
  if (fstat(fd, &stat) < 0) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  if (!fdt_floppy_params_setstat(params, &stat, err))
    return false;

  // Reset  FDGETPRM parameters (Operation not permitted)

  // if (ioctl(fd, FDRESET, FD_RESET_ALWAYS) < 0) {
  //   fdt_error_setlasterror(err, "");
  //   return false;
  // }

  // Check FDGETDRVPRM parameters

  struct floppy_drive_params fddprms;
  if (ioctl(fd, FDGETDRVPRM, &fddprms) != 0) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  bool is_success = fdt_floppy_params_setfloppydriveparams(params, &fddprms, err);

  // Check FDGETPRM parameters

  struct floppy_struct fdprms;
  if (ioctl(fd, FDGETPRM, &fdprms) != 0) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  if (!fdt_floppy_params_setfloppystruct(params, &fdprms, err)) {
    is_success = false;
  }

  if (!is_already_opened) {
    if (!fdt_device_close(dev, err))
      return false;
  }

  return is_success;
}

bool fdt_device_detecttransferrate(int fd, FdtFloppyParams* params, FdtError* err)
{
  floppy_raw_cmd raw_cmd;
  if (!fdt_floppy_rawcmd_readid(fd, fdt_floppy_params_getdeviceno(params), 0, 0, &raw_cmd))
    return false;

  fdt_floppy_rawcmd_print(&raw_cmd);
  return true;
}

bool fdt_device_detectfloppyformat(FdtDevice* dev, FdtFloppyParams* params, FdtError* err)
{
  if (!dev)
    return false;

  if (!fdt_device_getfloppyparameters(dev, params, err))
    return false;

  bool is_already_opened = fdt_device_isopened(dev);
  if (!is_already_opened) {
    if (!fdt_device_open(dev, fdt_device_getname(dev), FDT_FILE_READ, err)) {
      return false;
    }
  }

  int fd = fdt_device_getfileno(dev);
  if (fd == -1)
    return false;

  if (!is_already_opened) {
    if (!fdt_device_close(dev, err))
      return false;
  }

  if (!fdt_device_detecttransferrate(fd, params, err))
    return false;

  return true;
}

#endif /* __linux__ */
