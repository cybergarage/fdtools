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

#include <fdtools/error.h>
#include <fdtools/util/log.h>

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

  fdt_error_clear(err);

  return err;
}

bool fdt_error_delete(FdtError* err)
{
  if (!err)
    return false;

  fdt_string_delete(err->message);
  fdt_string_delete(err->debug_message);
  fdt_string_delete(err->file_name);
  fdt_string_delete(err->func_name);

  free(err);

  return true;
}

bool fdt_error_clear(FdtError* err)
{
  if (!err)
    return false;

  err->line_no = -1;
  fdt_string_clear(err->message);
  fdt_string_clear(err->file_name);
  fdt_string_clear(err->func_name);

  return true;
}

bool fdt_error_iserror(FdtError* err)
{
  if (!err)
    return false;

  if (0 < err->line_no)
    return true;

  if (0 < fdt_string_length(err->func_name))
    return true;

  if (0 < fdt_string_length(err->message))
    return true;

  return false;
}

bool fdt_error_setdebugmessage(FdtError* err, const char* file, int line_no, const char* function, const char* prefix, const char* format, ...)
{
  if (!err)
    return false;

  fdt_string_setvalue(err->file_name, file);
  err->line_no = line_no;
  fdt_string_setvalue(err->func_name, function);

  char msg[FDT_ERROR_MESSAGE_MAX];
  size_t prefix_len = 0;
  if (0 < fdt_strlen(prefix)) {
    prefix_len = snprintf(msg, sizeof(msg), "%s: ", prefix);
  }

  va_list list;
  va_start(list, format);
  vsnprintf((msg + prefix_len), (sizeof(msg) - prefix_len), format, list);
  va_end(list);

  fdt_string_setvalue(err->message, msg);

  return true;
}

bool fdt_error_appendmessage(FdtError* err, const char* format, ...)
{
  if (!err)
    return false;

  char msg[FDT_ERROR_MESSAGE_MAX];
  va_list list;
  va_start(list, format);
  vsnprintf(msg, sizeof(msg), format, list);
  va_end(list);

  fdt_string_appendvalue(err->message, " ");
  fdt_string_appendvalue(err->message, msg);

  return true;
}

const char* fdt_error_getdebugmessage(FdtError* err)
{
  if (!err)
    return "";

  char msg[FDT_ERROR_MESSAGE_MAX];
  if (fdt_error_iserror(err)) {
    snprintf(msg, sizeof(msg), "%s (%s())", fdt_string_getvalue(err->message), fdt_string_getvalue(err->func_name));
    fdt_string_setvalue(err->debug_message, msg);
  }
  else {
    fdt_string_setvalue(err->debug_message, "");
  }

#if defined(DEBUG)
  if (fdt_error_iserror(err)) {
    fdt_log_error("%s", fdt_string_getvalue(err->debug_message));
  }
#endif

  return fdt_string_getvalue(err->debug_message);
}

void fdt_error_printmessage(FdtError* err)
{
  if (!fdt_error_iserror(err))
    return;
  printf("%s\n", fdt_error_getmessage(err));
}

void fdt_error_printdebugmessage(FdtError* err)
{
#if defined(DEBUG)
  if (!fdt_error_iserror(err))
    return;
  printf("%s\n", fdt_error_getmessage(err));
#endif
}
