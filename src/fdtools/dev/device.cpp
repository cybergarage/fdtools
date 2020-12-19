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

FdtDevice* fdt_device_new()
{
  FdtDevice* dev = (FdtDevice*)calloc(sizeof(FdtDevice), 1);
  if (!dev) {
    return NULL;
  }

  dev->name = fdt_string_new();
  if (!dev->name) {
    fdt_device_delete(dev);
    return NULL;
  }

  dev->fd = -1;

  return dev;
}

bool fdt_device_delete(FdtDevice* dev)
{
  if (!dev)
    return false;

  if (fdt_device_isopened(dev)) {
    if (!fdt_device_close(dev, NULL)) {
      return false;
    }
  }

  if (dev->name) {
    fdt_string_delete(dev->name);
  }

  free(dev);

  return true;
}
