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

#include <string.h>

#include <fdtools/util/string.h>

/* Define amount of extra characters allocated on each realloc, with this we
   can avoid many small subsequent reallocs, which takes lots of time */
#define MUPNP_STRING_REALLOC_EXTRA 16

FdtString* fdt_string_new()
{
  FdtString* str = (FdtString*)malloc(sizeof(FdtString));
  if (!str)
    return NULL;

  str->value = NULL;
  str->memSize = 0;
  str->valueSize = 0;

  return str;
}

void fdt_string_delete(FdtString* str)
{
  if (!str)
    return;
  fdt_string_clear(str);
  free(str);
}

void fdt_string_clear(FdtString* str)
{
  if (!str)
    return;

  if (!str->value)
    return;

  free(str->value);
  str->value = NULL;
  str->memSize = 0;
  str->valueSize = 0;
}

void fdt_string_setvalue(FdtString* str, const char* value)
{
  fdt_string_setnvalue(str, value, fdt_strlen(value));
}

void fdt_string_setnvalue(FdtString* str, const char* value, size_t len)
{
  if (!str)
    return;

  fdt_string_clear(str);
  if (!value)
    return;

  str->valueSize = len;
  str->memSize = str->valueSize + 1;
  str->value = (char*)malloc(str->memSize * sizeof(char));

  if (!str->value)
    return;

  memcpy(str->value, value, len);
  str->value[len] = '\0';
}

char* fdt_string_getvalue(FdtString* str)
{
  return (str) ? str->value : NULL;
}

size_t fdt_string_length(FdtString* str)
{
  if (!str)
    return 0;

  if (!str->value)
    return 0;

  return str->valueSize;
}
