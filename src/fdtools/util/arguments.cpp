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

#include <fdtools/util/arguments.h>

FdtArguments* fdt_arguments_new()
{
  FdtArguments* args = (FdtArguments*)malloc(sizeof(FdtArguments));
  if (!args) {
    return NULL;
  }
  args->options = fdt_dictionary_new();

  if (!args->options) {
    fdt_arguments_delete(args);
    return NULL;
  }

  return args;
}

bool fdt_arguments_delete(FdtArguments* args)
{
  if (!args)
    return false;
  fdt_dictionary_delete(args->options);
  free(args);
  return true;
}
