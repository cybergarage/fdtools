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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <fdtools/error.h>

const size_t FDT_ERROR_MESSAGE_MAX = 256;

FdtError* fdt_error_new()
{
  FdtError* err = (FdtError*)calloc(1, sizeof(FdtError));
  if (!err) {
    return NULL;
  }

  err->message = fdt_string_new();
  err->debug_message = fdt_string_new();
  err->file_name = fdt_string_new();
  err->func_name = fdt_string_new();

  if (!err->message || !err->debug_message || !err->file_name || !err->func_name) {
    fdt_error_delete(err);
    return NULL;
  }

  return err;
}

void fdt_error_delete(FdtError* err)
{
  if (!err)
    return;

  if (err->message) {
    fdt_string_delete(err->message);
  }
  if (err->debug_message) {
    fdt_string_delete(err->debug_message);
  }
  if (err->file_name) {
    fdt_string_delete(err->file_name);
  }
  if (err->func_name) {
    fdt_string_delete(err->func_name);
  }

  free(err);
}

void fdt_error_setdebugmessage(FdtError* err, const char* file, int line_no, const char* function, const char* format, ...)
{
  fdt_string_setvalue(err->file_name, file);
  err->line_no = line_no;
  fdt_string_setvalue(err->func_name, function);

  va_list list;
  va_start(list, format);
  char msg[FDT_ERROR_MESSAGE_MAX];
  vsnprintf(msg, FDT_ERROR_MESSAGE_MAX, format, list);
  va_end(list);
}

const char* fdt_error_getdebugmessage(FdtError*err)
{
  char msg[FDT_ERROR_MESSAGE_MAX];
  snprintf(msg, FDT_ERROR_MESSAGE_MAX, "%s(): %s (%d:%s)", fdt_string_getvalue(err->func_name), fdt_string_getvalue(err->message), err->line_no, fdt_string_getvalue(err->file_name));
  fdt_string_setvalue(err->debug_message, msg);
  return fdt_string_getvalue(err->debug_message);
}
