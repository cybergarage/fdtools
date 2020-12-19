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

#include <fdtools/dev/device.h>

FdtFloppyParams* fdt_floppy_params_new()
{
  FdtFloppyParams* params = (FdtFloppyParams*)calloc(sizeof(FdtFloppyParams), 1);
  if (!params)
    return NULL;

  params->name = fdt_string_new();
  if (!params->name) {
    fdt_floppy_params_delete(params);
    return NULL;
  }

  return params;
}

bool fdt_floppy_params_delete(FdtFloppyParams* params)
{
  if (!params)
    return false;

  if (params->name) {
    fdt_string_delete(params->name);
  }

  free(params);

  return true;
}