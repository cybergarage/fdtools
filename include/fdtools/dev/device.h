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

#include <fdtools/error.h>
#include <fdtools/typedef.h>
#include <fdtools/util/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  FDT_FLOPPY_MEDIA_UNKNOWN,
  FDT_FLOPPY_MEDIA_8,
  FDT_FLOPPY_MEDIA_525,
  FDT_FLOPPY_MEDIA_35,
} FdtFloppyMedia;

typedef enum {
  FDT_FLOPPY_DENSITY_UNKNOWN,
  FDT_FLOPPY_DENSITY_SD,
  FDT_FLOPPY_DENSITY_DD,
  FDT_FLOPPY_DENSITY_QD,
  FDT_FLOPPY_DENSITY_HD,
  FDT_FLOPPY_DENSITY_ED
} FdtFloppyDensity;

typedef struct {
  FdtString* name;
  FdtFloppyMedia media;
  FdtFloppyDensity density;
  unsigned int size;
  unsigned int sect;
  unsigned int head;
  unsigned int track;
  unsigned int stretch;
  unsigned char gap;
  unsigned char rate;
  unsigned char spec1;
  unsigned char fmt_gap;
} FdtFloppyParams;

typedef enum {
  FDT_DEVICE_READ = 0x01,
  FDT_DEVICE_WRITE = 0x02,
} FdtDeviceMode;

typedef struct FDT_ATTR_PACKED {
  FdtString* name;
  int fd;
} FdtDevice;

FdtDevice* fdt_device_new();
void fdt_device_delete(FdtDevice*);

bool fdt_device_open(FdtDevice*, const char*, FdtDeviceMode, FdtError*);

#define fdt_device_setname(dev, v) fdt_string_setvalue(dev->name, v)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_DEV_DEVICE_H_ */
