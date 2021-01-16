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
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fdtools/dev/device.h>
#include <fdtools/dev/error.h>

#if defined(__linux__)
#define FDT_FD_2M FD_2M
#define FDT_FD_SIZECODEMASK FD_SIZECODEMASK
#define FDT_FD_SIZECODE(params) FD_SIZECODE(params)
#define FDT_FD_SECTSIZE(params) FD_SECTSIZE(params)
#else
// See <linux/fd.h>
#define FDT_FD_2M 0x4
#define FDT_FD_SIZECODEMASK 0x38
#define FDT_FD_SIZECODE(params) (((((params)->rate & FDT_FD_SIZECODEMASK) >> 3) + 2) % 8)
#define FDT_FD_SECTSIZE(params) ((params)->rate & FDT_FD_2M ? 512 : 128 << FDT_FD_SIZECODE(params))
#endif

FdtFloppyParams* fdt_floppy_params_new()
{
  FdtFloppyParams* params = (FdtFloppyParams*)calloc(sizeof(FdtFloppyParams), 1);
  if (!params)
    return NULL;

  params->name = fdt_string_new();
  params->desc = fdt_string_new();

  if (!params->name || !params->desc) {
    fdt_floppy_params_delete(params);
    return NULL;
  }

  return params;
}

bool fdt_floppy_params_delete(FdtFloppyParams* params)
{
  if (!params)
    return false;

  fdt_string_delete(params->name);
  fdt_string_delete(params->desc);

  free(params);

  return true;
}

bool fdt_floppy_params_setdrivetype(FdtFloppyParams* params, FdtFloppyDriveType drive_type, FdtError* err)
{
  if (!params)
    return false;

  switch (drive_type) {
  case FDT_FLOPPY_DRIVE_525_DD:
    fdt_floppy_params_setmedia(params, FDT_FLOPPY_MEDIA_525);
    fdt_floppy_params_setmaxdensity(params, FDT_FLOPPY_DENSITY_DD);
    fdt_floppy_params_setdensity(params, FDT_FLOPPY_DENSITY_DD);
    fdt_floppy_params_setdtr(params, FDT_FLOPPY_DTR_MFM_250KB, err);
    fdt_floppy_params_settpi(params, 48);
    fdt_floppy_params_setrpm(params, 300);
    break;
  case FDT_FLOPPY_DRIVE_525_HD:
    fdt_floppy_params_setmedia(params, FDT_FLOPPY_MEDIA_525);
    fdt_floppy_params_setmaxdensity(params, FDT_FLOPPY_DENSITY_HD);
    fdt_floppy_params_setdensity(params, FDT_FLOPPY_DENSITY_HD);
    fdt_floppy_params_setdtr(params, FDT_FLOPPY_DTR_MFM_500KB, err);
    fdt_floppy_params_settpi(params, 96);
    fdt_floppy_params_setrpm(params, 360);
    break;
  case FDT_FLOPPY_DRIVE_35_DD:
    fdt_floppy_params_setmedia(params, FDT_FLOPPY_MEDIA_35);
    fdt_floppy_params_setmaxdensity(params, FDT_FLOPPY_DENSITY_DD);
    fdt_floppy_params_setdensity(params, FDT_FLOPPY_DENSITY_DD);
    fdt_floppy_params_setdtr(params, FDT_FLOPPY_DTR_MFM_250KB, err);
    fdt_floppy_params_settpi(params, 96);
    fdt_floppy_params_setrpm(params, 300);
    break;
  case FDT_FLOPPY_DRIVE_35_HD:
    fdt_floppy_params_setmedia(params, FDT_FLOPPY_MEDIA_35);
    fdt_floppy_params_setmaxdensity(params, FDT_FLOPPY_DENSITY_HD);
    fdt_floppy_params_setdensity(params, FDT_FLOPPY_DENSITY_HD);
    fdt_floppy_params_setdtr(params, FDT_FLOPPY_DTR_MFM_500KB, err);
    fdt_floppy_params_settpi(params, 96);
    fdt_floppy_params_setrpm(params, 300);
    break;
  case FDT_FLOPPY_DRIVE_35_ED:
    fdt_floppy_params_setmedia(params, FDT_FLOPPY_MEDIA_35);
    fdt_floppy_params_setmaxdensity(params, FDT_FLOPPY_DENSITY_ED);
    fdt_floppy_params_setdensity(params, FDT_FLOPPY_DENSITY_ED);
    fdt_floppy_params_setdtr(params, FDT_FLOPPY_DTR_MFM_1000KB, err);
    fdt_floppy_params_settpi(params, 96);
    fdt_floppy_params_setrpm(params, 300);
    break;
  default:
    fdt_error_setmessage(err, FDT_DEVICE_FOLPPY_ERROR_UNKNOWN_DRIVE_TYPE_FORMAT, drive_type);
    return false;
  }

  return true;
}

bool fdt_floppy_params_setdtr(FdtFloppyParams* params, FdtFloppyDataTransferRate dtr, FdtError* err)
{
  params->dtr = dtr;

  switch (dtr) {
  case FDT_FLOPPY_DTR_MFM_500KB:
  case FDT_FLOPPY_DTR_MFM_1000KB:
    fdt_floppy_params_setgap1size(params, 27 /* 0x1b */);
    fdt_floppy_params_setgap2size(params, 108 /* 0x6c */);
    break;
  case FDT_FLOPPY_DTR_MFM_300KB:
    fdt_floppy_params_setgap1size(params, 35 /* 0x23 */);
    fdt_floppy_params_setgap2size(params, 108 /* 0x6c */);
    break;
  case FDT_FLOPPY_DTR_MFM_250KB:
    fdt_floppy_params_setgap1size(params, 42 /* 0x2a */);
    fdt_floppy_params_setgap2size(params, 108 /* 0x6c */);
    break;
  default:
    fdt_error_setmessage(err, FDT_DEVICE_FOLPPY_ERROR_UNKNOWN_DATA_TRANSFER_RATE_TYPE_FORMAT, dtr);
    return false;
  }

  return true;
}

size_t fdt_floppy_params_getssize(FdtFloppyParams* params)
{
  return FDT_FD_SECTSIZE(params);
}

const char* fdt_floppy_params_getmediastring(FdtFloppyParams* params)

{
  switch (params->media) {
  case FDT_FLOPPY_MEDIA_8:
    return "8";
  case FDT_FLOPPY_MEDIA_525:
    return "5.25 ";
  case FDT_FLOPPY_MEDIA_35:
    return "3.5";
  default:
    return "??";
  }

  return "??";
}

const char* fdt_floppy_params_getdensitystring(FdtFloppyParams* params)
{
  switch (params->density) {
  case FDT_FLOPPY_DENSITY_SD:
    return "SD";
  case FDT_FLOPPY_DENSITY_DD:
    return "DD";
  case FDT_FLOPPY_DENSITY_QD:
    return "QD";
  case FDT_FLOPPY_DENSITY_HD:
    return "HD";
  case FDT_FLOPPY_DENSITY_ED:
    return "ED";
  default:
    return "??";
  }

  return "??";
}

const char* fdt_floppy_params_getdescription(FdtFloppyParams* params)
{
  if (!params)
    return "";

  char desc[128];
  const char* media = fdt_floppy_params_getmediastring(params);
  const char* density = fdt_floppy_params_getdensitystring(params);
  snprintf(desc, sizeof(desc), "%s/%s, size=%ld track=%ld head=%ld sect=%ld stretch=%02X rate=%02X gap1=%ld gap2=%ld spec1=%02X", media, density, params->size, params->track, params->head, params->sect, params->stretch, params->rate, params->gap1, params->gap2, params->spec1);
  fdt_string_setvalue(params->desc, desc);
  return fdt_string_getvalue(params->desc);
}
