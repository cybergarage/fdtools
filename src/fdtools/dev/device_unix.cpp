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

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <fdtools/dev/device.h>

bool fdt_device_open(FdtDevice* dev, const char* name, FdtDeviceMode mode, FdtError* err)
{
  if (!dev)
    return false;

  dev->fd = -1;
  switch (mode) {
  case FDT_DEVICE_READ:
    dev->fd = open(name, O_RDONLY);
    break;
  case FDT_DEVICE_WRITE:
    dev->fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    break;
  }

  if (dev->fd < 0) {
    fdt_error_setlasterror(err, name);
    return false;
  }

  return true;
}

bool fdt_device_isopened(FdtDevice* dev)
{
  if (!dev)
    return false;
  return (dev->fd != -1) ? true : false;
}

bool fdt_device_close(FdtDevice* dev, FdtError* err)
{
  if (!dev)
    return false;
  if (dev->fd < 0)
    return true;

  if (close(dev->fd) != 0) {
    fdt_error_setlasterror(err, fdt_device_getname(dev));
    return false;
  }

  fdt_device_setname(dev, "");
  dev->fd = -1;

  return true;
}

bool fdt_device_readoffsetblock(FdtDevice* dev, off_t offset, byte_t* buf, size_t block_size, FdtError* err)
{
  if (!dev || (dev->fd < 0))
    return false;

  if (lseek(dev->fd, offset, SEEK_SET) == -1) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  ssize_t n_read = 0;
  while (n_read < block_size) {
    ssize_t n = read(dev->fd, buf + n_read, block_size - n_read);
    if (n == 0) // EOF
      break;
    if (0 < n) {
      n_read += n;
      continue;
    }
    fdt_error_setlasterror(err, "");
    break;
  }
  return (n_read == block_size) ? true : false;
}

bool fdt_device_writeoffsetblock(FdtDevice* dev, off_t offset, byte_t* buf, size_t block_size, FdtError* err)
{
  if (!dev || (dev->fd < 0))
    return false;

  if (lseek(dev->fd, offset, SEEK_SET) == -1) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  ssize_t n_wrote = 0;
  errno = 0;
  while (n_wrote < block_size) {
    errno = 0;
    ssize_t n = write(dev->fd, buf + n_wrote, block_size - n_wrote);
    if (0 < n) {
      n_wrote += n;
      continue;
    }
    if (n < 0) {
      fdt_error_setlasterror(err, "");
      break;
    }
  }

  return (n_wrote == block_size) ? true : false;
}
