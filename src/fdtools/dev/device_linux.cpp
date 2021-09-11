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
    if (!fdt_device_open(dev, FDT_FILE_READ, err)) {
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

bool fdt_device_detecttransferratewithrate(int fd, int rate, FdtFloppyParams* params, FdtError* err)
{
  // See: https://fdutils.linux.lu/disk-id.html
  // Finding out the data transfer rate - How to identify an unknown disk using Fdutils
  // First, you need to find out the data transfer rate (roughly the density: high, double, single).
  // For this, you try out fdrawcmd readid 0 rate=x, where x is 0, 1, 2, 3 If no rate is supplied, fdrawcmd assumes rate=0

  floppy_raw_cmd raw_cmd;
  if (!fdt_floppy_rawcmd_readid(fd, fdt_floppy_params_getdeviceno(params), rate, 0, &raw_cmd))
    return false;

  if (raw_cmd.reply_count < 7)
    return false;

  // The first 3 output bytes are error codes. The first byte should be below 7 (i.e. the example above succeeded).
  // The last four bytes is a sector header.
  // Byte 3 is the cylinder (here: 0), byte 4 is the head (here: 0).
  // Byte 5 is the sector number (here: 1) of the sector which happened to be near the R/W head when the command was issued.
  // Byte 6 is the sector size code. Size code 0 means 128 bytes per sector, size code 1 means 256 bytes per sector, size code 2 means 512 bytes per sector, etc (i.e. size doubles with each increment).
  // So, you try out all 4 rates until you get one that succeeds (byte 0 <= 7). If none matches, try adding the FM keyword (to use FM coding instead of MFM).

  return true;
}

bool fdt_device_detecttransferrate(int fd, FdtFloppyParams* params, FdtError* err)
{
  // See: http://man.he.net/man1/fdrawcmd
  // fdrawcmd
  // rate=rate
  // Selects  the data transfer rate. Use 0 for high density disks, 1
  // for double density 5 1/4 disks (or 2 Mbps tapes, if the  appropriate rate table is selected),
  // and 2 for double density 3 1/2 disks.

  int rates[] = {
    0x000,
    0x001,
    0x002,
    0x043,
    0x100,
  };

  for (int n = 0; n < 5; n++) {
    if (fdt_device_detecttransferratewithrate(fd, rates[n], params, err))
      return true;
  }

  return false;
}

bool fdt_device_detectfloppyformat(FdtDevice* dev, FdtFloppyParams* params, FdtError* err)
{
  if (!dev)
    return false;

  if (!fdt_device_getfloppyparameters(dev, params, err))
    return false;

  bool is_already_opened = fdt_device_isopened(dev);
  if (!is_already_opened) {
    if (!fdt_device_open(dev, FDT_FILE_READ, err)) {
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
