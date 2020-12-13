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

#ifndef _FDTOOLS_ERROR_H_
#define _FDTOOLS_ERROR_H_

#include <errno.h>
#include <string.h>

#include <fdtools/util/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  FdtString* message;
  FdtString* debug_message;
  FdtString* file_name;
  int line_no;
  FdtString* func_name;
} FdtError;

FdtError* fdt_error_new();
bool fdt_error_delete(FdtError*);

#if defined(__USE_ISOC99)
#define fdt_error_setmessage(err, format, ...) fdt_error_setdebugmessage(err, __FILE__, __LINE__, __func__, "", format, __VA_ARGS__)
#define fdt_error_setlasterror(err, format, ...) fdt_error_setdebugmessage(err, __FILE__, __LINE__, __func__, strerror(errno), format, __VA_ARGS__)
#else
#define fdt_error_setmessage(err, format...) fdt_error_setdebugmessage(err, __FILE__, __LINE__, __func__, "", format)
#define fdt_error_setlasterror(err, format...) fdt_error_setdebugmessage(err, __FILE__, __LINE__, __func__, strerror(errno), format)
#endif

#define fdt_error_getmessage(err) fdt_string_getvalue(err->message)

void fdt_error_setdebugmessage(FdtError*, const char*, int, const char*, const char*, const char*, ...);
const char* fdt_error_getdebugmessage(FdtError*);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _FDTOOLS_UTIL_LIST_H_ */
