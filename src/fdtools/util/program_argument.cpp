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

FdtProgramArgument* fdt_program_argument_new()
{
  FdtProgramArgument* arg = (FdtProgramArgument*)malloc(sizeof(FdtProgramArgument));
  if (!arg) {
    return NULL;
  }

  fdt_list_node_init((FdtList*)arg);
  arg->value = fdt_string_new();

  if (!arg->value) {
    fdt_program_argument_delete(arg);
    return NULL;
  }

  return arg;
}

bool fdt_program_argument_delete(FdtProgramArgument* arg)
{
  if (!arg)
    return true;
  fdt_list_remove((FdtList*)arg);
  fdt_string_delete(arg->value);
  free(arg);
  return true;
}
