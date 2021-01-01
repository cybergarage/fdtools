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

const mode_t FDT_DEVICE_WMODE = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

bool fdt_device_open(FdtDevice* dev, const char* name, FdtFileMode mode, FdtError* err)
{
  if (!dev)
    return false;

  int fd = -1;
  switch (mode) {
  case FDT_FILE_READ:
    fd = open(name, O_RDONLY);
    break;
  case FDT_FILE_WRITE:
    fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, FDT_DEVICE_WMODE);
    break;
  }

  if (fd == -1) {
    fdt_error_setlasterror(err, name);
    return false;
  }

  fdt_device_setfileno(dev, fd);

  return true;
}

bool fdt_device_isopened(FdtDevice* dev)
{
  if (!dev)
    return false;
  return (fdt_device_getfileno(dev) != -1) ? true : false;
}

bool fdt_device_close(FdtDevice* dev, FdtError* err)
{
  if (!dev)
    return false;

  int fd = fdt_device_getfileno(dev);
  if (fd < 0)
    return true;

  if (close(fd) != 0) {
    fdt_error_setlasterror(err, fdt_device_getname(dev));
    return false;
  }

  fdt_device_setname(dev, "");
  fdt_device_setfileno(dev, -1);

  return true;
}

bool fdt_device_readblock(FdtDevice* dev, byte_t* buf, size_t block_size, FdtError* err)
{
  return fdt_device_readoffsetblock(dev, -1, buf, block_size, err);
}

bool fdt_device_readoffsetblock(FdtDevice* dev, off_t offset, byte_t* buf, size_t block_size, FdtError* err)
{
  if (!dev)
    return false;

  int fd = fdt_device_getfileno(dev);
  if (fd == -1)
    return false;

  if (0 <= offset) {
    if (lseek(fd, offset, SEEK_SET) == -1) {
      fdt_error_setlasterror(err, "");
      return false;
    }
  }

  ssize_t n_read = 0;
  while (n_read < block_size) {
    ssize_t n = read(fd, buf + n_read, block_size - n_read);
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

bool fdt_device_writeblock(FdtDevice* dev, byte_t* buf, size_t block_size, FdtError* err)
{
  return fdt_device_writeoffsetblock(dev, -1, buf, block_size, err);
}

bool fdt_device_writeoffsetblock(FdtDevice* dev, off_t offset, byte_t* buf, size_t block_size, FdtError* err)
{
  if (!dev)
    return false;

  int fd = fdt_device_getfileno(dev);
  if (fd == -1)
    return false;

  if (0 <= offset) {
    if (lseek(fd, offset, SEEK_SET) == -1) {
      fdt_error_setlasterror(err, "");
      return false;
    }
  }

  ssize_t n_wrote = 0;
  errno = 0;
  while (n_wrote < block_size) {
    errno = 0;
    ssize_t n = write(fd, buf + n_wrote, block_size - n_wrote);
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

bool fdt_device_seek(FdtDevice* dev, off_t offset, int whence, FdtError* err)
{
  if (!dev)
    return false;

  int fd = fdt_device_getfileno(dev);
  if (fd == -1)
    return false;

  off_t pos = lseek(fd, offset, whence);
  if (pos == -1) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  return true;
}

ssize_t fdt_device_getsize(FdtDevice* dev, FdtError* err)
{
  if (!dev)
    return false;

  int fd = fdt_device_getfileno(dev);
  if (fd == -1)
    return false;

  off_t size = lseek(fd, 0, SEEK_END);
  if (size == -1) {
    fdt_error_setlasterror(err, "");
    return -1;
  }

  if (!fdt_device_seek(dev, 0, SEEK_SET, err))
    return -1;

  return size;
}
