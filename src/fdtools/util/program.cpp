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

#include <unistd.h>

#include <fdtools/util/program.h>

FdtProgram* fdt_program_new()
{
  FdtProgram* args = (FdtProgram*)malloc(sizeof(FdtProgram));
  if (!args) {
    return NULL;
  }

  args->args = (FdtArgumentList*)malloc(sizeof(FdtArgumentList));
  if (!args->args) {
    free(args);
    return NULL;
  }
  fdt_list_header_init((FdtList*)args->args);

  args->name = fdt_string_new();
  args->options = fdt_dictionary_new();
  if (!args->name || !args->options) {
    fdt_program_delete(args);
    return NULL;
  }

  return args;
}

bool fdt_program_delete(FdtProgram* args)
{
  if (!args)
    return false;
  fdt_list_clear((FdtList*)args->args, (FDT_LIST_DESTRUCTORFUNC)fdt_argument_delete);
  fdt_string_delete(args->name);
  fdt_dictionary_delete(args->options);
  free(args);
  return true;
}

bool fdt_program_parse(FdtProgram*, int argc, char * const argv[])
{
  return true;
}
