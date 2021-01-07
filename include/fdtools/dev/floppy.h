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

#ifndef _FDTOOLS_DEV_FLOPPY_H_
#define _FDTOOLS_DEV_FLOPPY_H_

#if defined(__linux__)
#include <linux/fd.h>
#include <linux/fdreg.h>
#include <linux/major.h>
#endif

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
  size_t size;
  size_t sect;
  size_t head;
  size_t track;
  int stretch;
  unsigned char gap;
  unsigned char rate;
  unsigned char spec1;
  unsigned char fmt_gap;
  FdtString* desc;
} FdtFloppyParams;

#define FDT_FLOPPY_STRETCH_DOUBLE_STEPS 0x01
#define FDT_FLOPPY_STRETCH_SWAP_SIDES 0x02

FdtFloppyParams* fdt_floppy_params_new();
bool fdt_floppy_params_delete(FdtFloppyParams*);

#define fdt_floppy_params_setname(dev, v) fdt_string_setvalue(dev->name = v)
#define fdt_floppy_params_setmedia(params, v) (params->media = v)
#define fdt_floppy_params_setdensity(params, v) (params->density = v)
#define fdt_floppy_params_setsize(params, v) (params->size = v)
#define fdt_floppy_params_setsect(params, v) (params->sect = v)
#define fdt_floppy_params_sethead(params, v) (params->head = v)
#define fdt_floppy_params_settrack(params, v) (params->track = v)
#define fdt_floppy_params_setstretch(params, v) (params->stretch = v)
#define fdt_floppy_params_setgap(params, v) (params->gap = v)
#define fdt_floppy_params_setrate(params, v) (params->rate = v)
#define fdt_floppy_params_setspec1(params, v) (params->spec1 = v)
#define fdt_floppy_params_setfmtgap(params, v) (params->fmt_gap = v)

size_t fdt_floppy_params_getssize(FdtFloppyParams*);
const char* fdt_floppy_params_getdensitystring(FdtFloppyParams*);
const char* fdt_floppy_params_getdescription(FdtFloppyParams*);

#define fdt_floppy_params_getname (dev) fdt_string_getvalue(dev->name)
#define fdt_floppy_params_getmedia(params) (params->media)
#define fdt_floppy_params_getdensity(params) (params->density)
#define fdt_floppy_params_getsize(params) (params->size)
#define fdt_floppy_params_getsect(params) (params->sect)
#define fdt_floppy_params_gethead(params) (params->head)
#define fdt_floppy_params_gettrack(params) (params->track)
#define fdt_floppy_params_getstretch(params) (params->stretch)
#define fdt_floppy_params_isdoublesteps(params) ((params->stretch & FDT_FLOPPY_STRETCH_DOUBLE_STEPS) ? true : false)
#define fdt_floppy_params_isswapsides(params) ((params->stretch & FDT_FLOPPY_STRETCH_SWAP_SIDES) ? true : false)
#define fdt_floppy_params_getgap(params) (params->gap)
#define fdt_floppy_params_getrate(params) (params->rate)
#define fdt_floppy_params_getspec1(params) (params->spec1)
#define fdt_floppy_params_getfmtgap(params) (params->fmt_gap)

#if defined(__linux__)
bool fdt_floppy_struct_setfloppystruct(floppy_struct*, FdtFloppyParams*, FdtError*);
bool fdt_floppy_params_setfloppystruct(FdtFloppyParams*, floppy_struct*, FdtError*);
#endif

#ifdef __cplusplus

} /* extern C */
#endif

#endif /* _FDTOOLS_DEV_FLOPPY_H_ */
