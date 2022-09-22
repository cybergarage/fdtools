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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fdtools/util/string.h>

FdtStrings* fdt_strings_new()
{
  FdtStrings* strs = (FdtStrings*)malloc(sizeof(FdtStrings));
  if (!strs) {
    return NULL;
  }

  fdt_list_header_init((FdtList*)strs);

  return strs;
}

void fdt_strings_delete(FdtStrings* strs)
{
  fdt_strings_clear(strs);
  free(strs);
}

void fdt_strings_addcstring(FdtStrings* strs, const char* value)
{
  FdtString* str = fdt_string_new();
  if (!str)
    return;
  fdt_string_setvalue(str, value);
  fdt_strings_addstring(strs, str);
}
