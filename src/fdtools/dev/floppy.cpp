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

size_t fdt_floppy_params_getssize(FdtFloppyParams* params)
{
  return FDT_FD_SECTSIZE(params);
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
  const char* density = fdt_floppy_params_getdensitystring(params);
  snprintf(desc, sizeof(desc), "%s, size=%ld track=%ld head=%ld sect=%ld stretch=%02X gap=%02X rate=%02X spec1=%02X, gap2=%02X", density, params->size, params->track, params->head, params->sect, params->stretch, params->rate, params->gap, params->spec1, params->fmt_gap);
  fdt_string_setvalue(params->desc, desc);
  return fdt_string_getvalue(params->desc);
}
