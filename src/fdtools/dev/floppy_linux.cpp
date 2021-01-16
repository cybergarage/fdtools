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

#include <fdtools/dev/error.h>
#include <fdtools/dev/floppy.h>

bool fdt_floppy_struct_setfloppyparams(floppy_struct* fdparams, FdtFloppyParams* params, FdtError* err)
{
  if (!params->track || !params->head || !params->sect) {
    fdt_error_setmessage(err, FDT_DEVICE_FOLPPY_ERROR_INVALID_PARAMETORE_FORMAT, fdt_floppy_params_getdescription(params));
    return false;
  }

  fdparams->track = fdt_floppy_params_gettrack(params);
  fdparams->head = fdt_floppy_params_gethead(params);
  fdparams->sect = fdt_floppy_params_getsect(params);
  fdparams->size = fdt_floppy_params_getsize(params);

  if (fdparams->size <= 0) {
    fdt_error_setmessage(err, FDT_DEVICE_FOLPPY_ERROR_INVALID_PARAMETORE_FORMAT, fdt_floppy_params_getdescription(params));
    return false;
  }

  fdparams->stretch = fdt_floppy_params_getstretch(params);
	fdparams->gap = fdt_floppy_params_getgap1size(params);
  /*
	fdparams->rate =
  */
	fdparams->spec1 = 0;
	fdparams->fmt_gap = fdt_floppy_params_getgap2size(params);

  return true;
}

bool fdt_floppy_params_setfloppydriveparams(FdtFloppyParams* params, floppy_drive_params* fddprms, FdtError* err)
{
  if (!params || !fddprms)
    return false;

  int cmos = fddprms->cmos;
  switch (cmos) {
  case 1: //5 1/4 DD
    fdt_floppy_params_setdrivetype(params, FDT_FLOPPY_DRIVE_525_DD, err);
    break;
  case 2: // 5 1/4 HD
    fdt_floppy_params_setdrivetype(params, FDT_FLOPPY_DRIVE_525_HD, err);
    break;
  case 3: // 3 1/2 DD
    fdt_floppy_params_setdrivetype(params, FDT_FLOPPY_DRIVE_35_DD, err);
    break;
  case 4: // 3 1/2 HD
    fdt_floppy_params_setdrivetype(params, FDT_FLOPPY_DRIVE_35_HD, err);
    break;
  case 5: // 3 1/2 ED
  case 6: // 3 1/2 ED
    fdt_floppy_params_setdrivetype(params, FDT_FLOPPY_DRIVE_35_ED, err);
    break;
  default:
    fdt_error_setmessage(err, FDT_DEVICE_FOLPPY_ERROR_UNKNOWN_CMOS_FORMAT, cmos);
    return false;
  }

  return true;
}

bool fdt_floppy_params_setfloppystruct(FdtFloppyParams* params, floppy_struct* fdprms, FdtError* err)
{
  if (!params || !fdprms)
    return false;

  fdt_floppy_params_setsect(params, fdprms->sect);
  fdt_floppy_params_sethead(params, fdprms->head);
  fdt_floppy_params_settrack(params, fdprms->track);
  fdt_floppy_params_setstretch(params, fdprms->stretch);
  fdt_floppy_params_setgap1size(params, fdprms->gap);
  fdt_floppy_params_setrate(params, fdprms->rate);
  fdt_floppy_params_setspec1(params, fdprms->spec1);
  fdt_floppy_params_setgap2size(params, fdprms->fmt_gap);

  return true;
}
