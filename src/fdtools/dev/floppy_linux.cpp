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

#include <fdtools/dev/floppy.h>

bool fdt_floppy_struct_setfloppystruct(floppy_struct* fdparams, FdtFloppyParams* params, FdtError* err)
{
  /*
  fdparams->size =
	fdparams->sect =
	fdparams->head =
	fdparams->track =
	fdparams->stretch =
	fdparams->gap = 
	fdparams->rate =
	fdparams->spec1 =
	fdparams->fmt_gap =
  */
 
  return true;
}

bool fdt_floppy_params_setfloppystruct(FdtFloppyParams* params, floppy_struct* fdprms, FdtError* err)
{
  if (!fdprms || !params)
    return false;

  fdt_floppy_params_setsize(params, fdprms->size);
  fdt_floppy_params_setsect(params, fdprms->sect);
  fdt_floppy_params_sethead(params, fdprms->head);
  fdt_floppy_params_settrack(params, fdprms->track);
  fdt_floppy_params_setstretch(params, fdprms->stretch);
  fdt_floppy_params_setgap(params, fdprms->gap);
  fdt_floppy_params_setrate(params, fdprms->rate);
  fdt_floppy_params_setspec1(params, fdprms->spec1);
  fdt_floppy_params_setfmtgap(params, fdprms->fmt_gap);

  return true;
}

