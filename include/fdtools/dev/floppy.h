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

typedef enum {
  FDT_FLOPPY_DTR_UNKNOWN,
  FDT_FLOPPY_DTR_FM_250KB = 1,
  FDT_FLOPPY_DTR_FM_150KB = 2,
  FDT_FLOPPY_DTR_FM_125KB = 3,
  FDT_FLOPPY_DTR_FM_500KB = 4,
  FDT_FLOPPY_DTR_MFM_500KB = 1,
  FDT_FLOPPY_DTR_MFM_300KB = 2,
  FDT_FLOPPY_DTR_MFM_250KB = 3,
  FDT_FLOPPY_DTR_MFM_1000KB = 4
} FdtFloppyDataTransferRate;

typedef enum {
  FDT_FLOPPY_TRACK_CAPACITY_UNKNOWN = 0,
  FDT_FLOPPY_TRACK_CAPACITY_2500 = 2500,
  FDT_FLOPPY_TRACK_CAPACITY_6250 = 6250,
  FDT_FLOPPY_TRACK_CAPACITY_7500 = 7500,
  FDT_FLOPPY_TRACK_CAPACITY_10416 = 10416,
  FDT_FLOPPY_TRACK_CAPACITY_12500 = 12500,
  FDT_FLOPPY_TRACK_CAPACITY_25000 = 25000,
} FdtFloppyTrackCapacity;

typedef enum {
  FDT_FLOPPY_DRIVE_UNKNOWN,
  FDT_FLOPPY_DRIVE_525_DD,
  FDT_FLOPPY_DRIVE_525_HD,
  FDT_FLOPPY_DRIVE_35_DD,
  FDT_FLOPPY_DRIVE_35_HD,
  FDT_FLOPPY_DRIVE_35_ED,
} FdtFloppyDriveType;

typedef struct {
  FdtString* name;
  FdtFloppyMedia media;
  FdtFloppyDensity density;
  FdtFloppyDensity max_density;
  FdtFloppyDataTransferRate dtr;
  int tpi;
  int rpm;
  size_t sect;
  size_t head;
  size_t track;
  int stretch;
  size_t gap1;
  size_t gap2;
  unsigned char rate;
  unsigned char spec1;
  FdtString* desc;
} FdtFloppyParams;

#define FDT_FLOPPY_STRETCH_DOUBLE_STEPS 0x01
#define FDT_FLOPPY_STRETCH_SWAP_SIDES 0x02

FdtFloppyParams* fdt_floppy_params_new();
bool fdt_floppy_params_delete(FdtFloppyParams*);

bool fdt_floppy_params_setdrivetype(FdtFloppyParams*, FdtFloppyDriveType, FdtError*);
bool fdt_floppy_params_setdtr(FdtFloppyParams*, FdtFloppyDataTransferRate, FdtError*);

#define fdt_floppy_params_setname(dev, v) fdt_string_setvalue(dev->name = v)
#define fdt_floppy_params_setmedia(params, v) (params->media = v)
#define fdt_floppy_params_setmaxdensity(params, v) (params->max_density = v)
#define fdt_floppy_params_setdensity(params, v) (params->density = v)
#define fdt_floppy_params_settpi(params, v) (params->tpi = v)
#define fdt_floppy_params_setrpm(params, v) (params->rpm = v)
#define fdt_floppy_params_setsect(params, v) (params->sect = v)
#define fdt_floppy_params_sethead(params, v) (params->head = v)
#define fdt_floppy_params_settrack(params, v) (params->track = v)
#define fdt_floppy_params_setstretch(params, v) (params->stretch = v)
#define fdt_floppy_params_setgap1size(params, v) (params->gap1 = v)
#define fdt_floppy_params_setgap2size(params, v) (params->gap2 = v)
#define fdt_floppy_params_setrate(params, v) (params->rate = v)
#define fdt_floppy_params_setspec1(params, v) (params->spec1 = v)

FdtFloppyDriveType fdt_floppy_params_getdrivetype(FdtFloppyParams*);
size_t fdt_floppy_params_gettrackcapacity(FdtFloppyParams* params);
size_t fdt_floppy_params_getsize(FdtFloppyParams*);
size_t fdt_floppy_params_getssize(FdtFloppyParams*);
const char* fdt_floppy_params_getmediastring(FdtFloppyParams*);
const char* fdt_floppy_params_getdensitystring(FdtFloppyParams*);
const char* fdt_floppy_params_getdescription(FdtFloppyParams*);

#define fdt_floppy_params_getname (dev) fdt_string_getvalue(dev->name)
#define fdt_floppy_params_getmedia(params) (params->media)
#define fdt_floppy_params_getmaxdensity(params) (params->max_density)
#define fdt_floppy_params_getdensity(params) (params->density)
#define fdt_floppy_params_getdtr(params) (params->dtr)
#define fdt_floppy_params_gettpi(params) (params->tpi)
#define fdt_floppy_params_getrpm(params) (params->rpm)
#define fdt_floppy_params_getsect(params) (params->sect)
#define fdt_floppy_params_gethead(params) (params->head)
#define fdt_floppy_params_gettrack(params) (params->track)
#define fdt_floppy_params_getstretch(params) (params->stretch)
#define fdt_floppy_params_isdoublesteps(params) ((params->stretch & FDT_FLOPPY_STRETCH_DOUBLE_STEPS) ? true : false)
#define fdt_floppy_params_isswapsides(params) ((params->stretch & FDT_FLOPPY_STRETCH_SWAP_SIDES) ? true : false)
#define fdt_floppy_params_getgap1size(params) (params->gap1)
#define fdt_floppy_params_getgap2size(params) (params->gap2)
#define fdt_floppy_params_getrate(params) (params->rate)
#define fdt_floppy_params_getspec1(params) (params->spec1)

#if defined(__linux__)
bool fdt_floppy_struct_equals(struct floppy_struct*, struct floppy_struct*);
bool fdt_floppy_struct_setfloppyparams(struct floppy_struct*, FdtFloppyParams*, FdtError*);
bool fdt_floppy_params_setfloppydriveparams(FdtFloppyParams*, struct floppy_drive_params*, FdtError*);
bool fdt_floppy_params_setfloppystruct(FdtFloppyParams*, struct floppy_struct*, FdtError*);
#endif

#ifdef __cplusplus

} /* extern C */
#endif

#endif /* _FDTOOLS_DEV_FLOPPY_H_ */
