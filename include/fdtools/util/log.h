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

#ifndef _FDTOOLS_UTIL_LOG_H_
#define _FDTOOLS_UTIL_LOG_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_LOG_BUF 2048

#define FDT_LOG_NONE 0
#define FDT_LOG_ERROR 1
#define FDT_LOG_WARN 2
#define FDT_LOG_INFO 4
#define FDT_LOG_DEBUG 8

#define FDT_LOG_ERROR_PREFIX "ERROR"
#define FDT_LOG_WARN_PREFIX "WARN"
#define FDT_LOG_INFO_PREFIX "INFO"
#define FDT_LOG_DEBUG_PREFIX "DEBUG"

#define LOG_ALL (FDT_LOG_ERROR | FDT_LOG_WARN | FDT_LOG_INFO | FDT_LOG_DEBUG)

void fdt_log_setlevel(int level);
void fdt_log_output(int level, const char* file, int line_n, const char* function, const char* format, ...);

#if defined(DEBUG)

#if defined(__USE_ISOC99)
#define fdt_log_error(format, ...) fdt_log_output(FDT_LOG_ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#define fdt_log_warn(format, ...) fdt_log_output(FDT_LOG_WARN, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#define fdt_log_info(format, ...) fdt_log_output(FDT_LOG_INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#define fdt_log_debug(format, ...) fdt_log_output(FDT_LOG_DEBUG, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#else
#define fdt_log_error(format...) fdt_log_output(FDT_LOG_ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
#define fdt_log_warn(format...) fdt_log_output(FDT_LOG_WARN, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
#define fdt_log_info(format...) fdt_log_output(FDT_LOG_INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
#define fdt_log_debug(format...) fdt_log_output(FDT_LOG_DEBUG, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
#endif

#else

#if defined(__USE_ISOC99)
#define fdt_log_error(format, ...)
#define fdt_log_warn(format, ...)
#define fdt_log_info(format, ...)
#define fdt_log_debug(format, ...)
#else
#define fdt_log_error(format...)
#define fdt_log_warn(format...)
#define fdt_log_info(format...)
#define fdt_log_debug(format...)
#endif

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _FDTOOLS_UTIL_LOG_H_ */
