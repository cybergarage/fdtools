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

#ifndef _FDTOOLS_DEV_DEVICE_H_
#define _FDTOOLS_DEV_DEVICE_H_

#include <stdio.h>
#include <sys/types.h>

#include <fdtools/dev/floppy.h>
#include <fdtools/util/file.h>
#include <fdtools/util/string.h>

#ifdef __cplusplus
extern "C" {
#endif

const char FDT_DEVICE_PREFIX[] = "/dev/";

typedef struct FDT_ATTR_PACKED {
  FdtString* name;
  int fd;
} FdtDevice;

FdtDevice* fdt_device_new();
bool fdt_device_delete(FdtDevice*);

bool fdt_device_open(FdtDevice*, FdtFileMode, FdtError*);
bool fdt_device_close(FdtDevice*, FdtError*);
bool fdt_device_isopened(FdtDevice*);
bool fdt_device_readblock(FdtDevice*, byte_t*, size_t, FdtError*);
bool fdt_device_writeblock(FdtDevice*, byte_t*, size_t, FdtError*);
bool fdt_device_readoffsetblock(FdtDevice*, off_t, byte_t*, size_t, FdtError*);
bool fdt_device_writeoffsetblock(FdtDevice*, off_t, byte_t*, size_t, FdtError*);
bool fdt_device_seek(FdtDevice*, off_t, int, FdtError*);
ssize_t fdt_device_getsize(FdtDevice*, FdtError*);

inline void fdt_device_setname(FdtDevice* dev, const char* v) { fdt_string_setvalue(dev->name, v); }
inline void fdt_device_setfileno(FdtDevice* dev, int v) { (dev->fd = v); }

inline const char* fdt_device_getname(FdtDevice* dev) { return fdt_string_getvalue(dev->name); }
inline int fdt_device_getfileno(FdtDevice* dev) { return dev->fd; }

bool fdt_device_getfloppyparameters(FdtDevice*, FdtFloppyParams*, FdtError*);
bool fdt_device_detectfloppyformat(FdtDevice*, FdtFloppyParams*, FdtError*);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_DEV_DEVICE_H_ */
