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

#define LOG_ERROR 1
#define LOG_WARNING 2
#define LOG_INFO 4
#define LOG_DEBUG 8

#define LOG_ERROR_S "ERROR"
#define LOG_WARNING_S "WARN"
#define LOG_INFO_S "INFO"
#define LOG_DEBUG_S "DEBUG"

#define LOG_ALL (LOG_ERROR | LOG_WARNING | LOG_INFO | LOG_DEBUG)

void fdt_log_output(int severity, const char* file, int line_n, const char* function, const char* format, ...);

#if defined(DEBUG)

#if defined(__USE_ISOC99)
#define fdt_log_error(format, ...) fdt_log_output(LOG_ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#define fdt_log_warn(format, ...) fdt_log_output(LOG_WARNING, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#define fdt_log_info(format, ...) fdt_log_output(LOG_INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#define fdt_log_debug(format, ...) fdt_log_output(LOG_DEBUG, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#else
#define fdt_log_error(format...) fdt_log_output(LOG_ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
#define fdt_log_warn(format...) fdt_log_output(LOG_WARNING, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
#define fdt_log_info(format...) fdt_log_output(LOG_INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
#define fdt_log_debug(format...) fdt_log_output(LOG_DEBUG, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
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
