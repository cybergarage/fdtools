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

/* Define amount of extra characters allocated on each realloc, with this we
   can avoid many small subsequent reallocs, which takes lots of time */
#define MUPNP_STRING_REALLOC_EXTRA 16

FdtString* fdt_string_new()
{
  FdtString* str = (FdtString*)malloc(sizeof(FdtString));
  if (!str)
    return NULL;

  fdt_list_node_init((FdtListNode*)str);

  str->value = NULL;
  str->mem_size = 0;
  str->value_size = 0;

  return str;
}

bool fdt_string_delete(FdtString* str)
{
  if (!str)
    return false;
  fdt_string_clear(str);
  free(str);
  return true;
}

bool fdt_string_clear(FdtString* str)
{
  if (!str)
    return false;

  if (!str->value)
    return true;

  free(str->value);

  str->value = NULL;
  str->mem_size = 0;
  str->value_size = 0;

  return true;
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

  str->value_size = len;
  str->mem_size = str->value_size + 1;
  str->value = (char*)malloc(str->mem_size * sizeof(char));

  if (!str->value)
    return;

  memcpy(str->value, value, len);
  str->value[len] = '\0';
}

const char* fdt_string_getvalue(FdtString* str)
{
  return (str) ? str->value : NULL;
}

size_t fdt_string_length(FdtString* str)
{
  if (!str)
    return 0;

  if (!str->value)
    return 0;

  return str->value_size;
}

bool fdt_string_equals(FdtString* str, FdtString* other)
{
  return fdt_streq(fdt_string_getvalue(str), fdt_string_getvalue(other));
}

bool fdt_string_appendvalue(FdtString* str, const char* value)
{
  return fdt_string_appendnvalue(str, value, fdt_strlen(value));
}

void fdt_string_setvaluef(FdtString* str, const char* format, ...)
{
  if (!str)
    return;

  char value[512];
  va_list list;
  va_start(list, format);
  vsnprintf(value, sizeof(value), format, list);
  va_end(list);

  fdt_string_setvalue(str, value);
}

bool fdt_string_appendnvalue(FdtString* str, const char* value, size_t valueLen)
{
  if (!str)
    return false;

  if (!value || valueLen <= 0)
    return true;

  size_t new_mem_size = str->value_size + valueLen + 1;
  if (new_mem_size > str->mem_size || str->value == NULL) {
    new_mem_size += MUPNP_STRING_REALLOC_EXTRA;
    char* new_value = new_value = (char*)realloc(str->value, new_mem_size * sizeof(char));
    if (!new_value)
      return false;

    str->mem_size = new_mem_size;
    str->value = new_value;
  }

  memcpy(str->value + str->value_size, value, valueLen);
  str->value_size += valueLen;
  str->value[str->value_size] = '\0';

  return true;
}
