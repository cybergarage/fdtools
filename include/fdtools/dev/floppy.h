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
#include <sys/stat.h>
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
  int deviceno;
  int tpi;
  int rpm;
  size_t sect;
  size_t head;
  size_t track;
  int stretch;
  size_t gap1;
  size_t gap2;
  byte_t rate;
  byte_t spec1;
  FdtString* desc;
} FdtFloppyParams;

const int FDT_FLOPPY_STRETCH_DOUBLE_STEPS = 0x01;
const int FDT_FLOPPY_STRETCH_SWAP_SIDES = 0x02;

FdtFloppyParams* fdt_floppy_params_new();
bool fdt_floppy_params_delete(FdtFloppyParams*);

bool fdt_floppy_params_setdrivetype(FdtFloppyParams*, FdtFloppyDriveType, FdtError*);
bool fdt_floppy_params_setdtr(FdtFloppyParams*, FdtFloppyDataTransferRate, FdtError*);

inline void fdt_floppy_params_setname(FdtFloppyParams* params, const char* v) { fdt_string_setvalue(params->name, v); }
inline void fdt_floppy_params_setmedia(FdtFloppyParams* params, FdtFloppyMedia v) { params->media = v; }
inline void fdt_floppy_params_setmaxdensity(FdtFloppyParams* params, FdtFloppyDensity v) { params->max_density = v; }
inline void fdt_floppy_params_setdensity(FdtFloppyParams* params, FdtFloppyDensity v) { params->density = v; }
inline void fdt_floppy_params_setdeviceno(FdtFloppyParams* params, int v) { params->deviceno = v; }
inline void fdt_floppy_params_settpi(FdtFloppyParams* params, int v) { params->tpi = v; }
inline void fdt_floppy_params_setrpm(FdtFloppyParams* params, int v) { params->rpm = v; }
inline void fdt_floppy_params_setsect(FdtFloppyParams* params, size_t v) { params->sect = v; }
inline void fdt_floppy_params_sethead(FdtFloppyParams* params, size_t v) { params->head = v; }
inline void fdt_floppy_params_settrack(FdtFloppyParams* params, size_t v) { params->track = v; }
inline void fdt_floppy_params_setstretch(FdtFloppyParams* params, int v) { params->stretch = v; }
inline void fdt_floppy_params_setgap1size(FdtFloppyParams* params, size_t v) { params->gap1 = v; }
inline void fdt_floppy_params_setgap2size(FdtFloppyParams* params, size_t v) { params->gap2 = v; }
inline void fdt_floppy_params_setrate(FdtFloppyParams* params, byte_t v) { params->rate = v; }
inline void fdt_floppy_params_setspec1(FdtFloppyParams* params, byte_t v) { params->spec1 = v; }

FdtFloppyDriveType fdt_floppy_params_getdrivetype(FdtFloppyParams*);
size_t fdt_floppy_params_gettrackcapacity(FdtFloppyParams* params);
size_t fdt_floppy_params_getsize(FdtFloppyParams*);
size_t fdt_floppy_params_getssize(FdtFloppyParams*);
const char* fdt_floppy_params_getmediastring(FdtFloppyParams*);
const char* fdt_floppy_params_getdensitystring(FdtFloppyParams*);
const char* fdt_floppy_params_getdescription(FdtFloppyParams*);

inline const char* fdt_floppy_params_getname(FdtFloppyParams* params) { return fdt_string_getvalue(params->name); }
inline FdtFloppyMedia fdt_floppy_params_getmedia(FdtFloppyParams* params) { return params->media; }
inline FdtFloppyDensity fdt_floppy_params_getmaxdensity(FdtFloppyParams* params) { return params->max_density; }
inline FdtFloppyDensity fdt_floppy_params_getdensity(FdtFloppyParams* params) { return params->density; }
inline int fdt_floppy_params_getdeviceno(FdtFloppyParams* params) { return params->deviceno; }
inline FdtFloppyDataTransferRate fdt_floppy_params_getdtr(FdtFloppyParams* params) { return params->dtr; }
inline int fdt_floppy_params_gettpi(FdtFloppyParams* params) { return params->tpi; }
inline int fdt_floppy_params_getrpm(FdtFloppyParams* params) { return params->rpm; }
inline size_t fdt_floppy_params_getsect(FdtFloppyParams* params) { return params->sect; }
inline size_t fdt_floppy_params_gethead(FdtFloppyParams* params) { return params->head; }
inline size_t fdt_floppy_params_gettrack(FdtFloppyParams* params) { return params->track; }
inline int fdt_floppy_params_getstretch(FdtFloppyParams* params) { return params->stretch; }
inline bool fdt_floppy_params_isdoublesteps(FdtFloppyParams* params) { return (params->stretch & FDT_FLOPPY_STRETCH_DOUBLE_STEPS) ? true : false; }
inline bool fdt_floppy_params_isswapsides(FdtFloppyParams* params) { return (params->stretch & FDT_FLOPPY_STRETCH_SWAP_SIDES) ? true : false; }
inline size_t fdt_floppy_params_getgap1size(FdtFloppyParams* params) { return params->gap1; }
inline size_t fdt_floppy_params_getgap2size(FdtFloppyParams* params) { return params->gap2; }
inline byte_t fdt_floppy_params_getrate(FdtFloppyParams* params) { return params->rate; }
inline byte_t fdt_floppy_params_getspec1(FdtFloppyParams* params) { return params->spec1; }

#if defined(__linux__)
bool fdt_floppy_struct_equals(struct floppy_struct*, struct floppy_struct*);
bool fdt_floppy_struct_setfloppyparams(struct floppy_struct*, FdtFloppyParams*, FdtError*);
bool fdt_floppy_params_setstat(FdtFloppyParams*, struct stat*, FdtError*);
bool fdt_floppy_params_setfloppydriveparams(FdtFloppyParams*, struct floppy_drive_params*, FdtError*);
bool fdt_floppy_params_setfloppystruct(FdtFloppyParams*, struct floppy_struct*, FdtError*);
#endif

#if defined(__linux__)
bool fdt_floppy_rawcmd_readid(int, int, int, int, struct floppy_raw_cmd*);
void fdt_floppy_rawcmd_print(struct floppy_raw_cmd* raw_cmd);
#endif

#ifdef __cplusplus

} /* extern C */
#endif

#endif /* _FDTOOLS_DEV_FLOPPY_H_ */
