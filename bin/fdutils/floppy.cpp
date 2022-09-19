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

#include "floppy.h"

void fdu_program_add_floppy_options(FdtProgram* prg)
{
  fdt_program_addoption(prg, OPT_CYLINDERS, "number of cylinders", true, "");
  fdt_program_addoption(prg, OPT_HEADS, "number of heads", true, "");
  fdt_program_addoption(prg, OPT_SECTORS, "number of sectors", true, "");
  fdt_program_addoption(prg, OPT_SSIZE, "sector size", true, "");
  fdt_program_addoption(prg, OPT_RETRY_PASSES, "number of retry passes", false, "");
}
