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

#include <fdtools/util/program.h>

FdtProgramArguments* fdt_program_arguments_new()
{
  FdtProgramArgument* args = (FdtProgramArguments*)malloc(sizeof(FdtProgramArguments));
  if (!args) {
    return NULL;
  }
  fdt_list_header_init((FdtList*)args);
  return args;
}

bool fdt_program_arguments_delete(FdtProgramArguments* args)
{
  if (!args)
    return true;
  fdt_program_arguments_clear(args);
  free(args);
  return true;
}

bool fdt_program_arguments_add(FdtProgramArguments* args, const char* value)
{
  FdtProgramArgument* arg = fdt_program_argument_new();
  if (!arg)
    return false;
  fdt_program_argument_setvalue(arg, value);
  fdt_list_add((FdtList*)args, (FdtList*)arg);
  return true;
}
