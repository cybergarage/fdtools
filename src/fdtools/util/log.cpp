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
#include <time.h>

#include <fdtools/util/log.h>

static const char* log_error_s = LOG_ERROR_S;
static const char* log_warning_s = LOG_WARNING_S;
static const char* log_info_s = LOG_INFO_S;
static const char* log_debug_s = LOG_DEBUG_S;

static const char* fdt_log_type2string(int type)
{
  switch (type) {
  case LOG_ERROR:
    return log_error_s;
    break;

  case LOG_WARNING:
    return log_warning_s;
    break;

  case LOG_INFO:
    return log_info_s;
    break;

  case LOG_DEBUG:
    return log_debug_s;
    break;
  }

  return "";
}

void fdt_log_output(int severity, const char* file, int line_n, const char* function, const char* format, ...)
{
  va_list list;

  char msg[MAX_LOG_BUF], tsPrefix[MAX_LOG_BUF];
  time_t ts;
  struct tm* localts;
  size_t prefixLen = -1;

  ts = time(NULL);
  localts = localtime(&ts);

  strftime(tsPrefix, MAX_LOG_BUF, "%c", localts);

  prefixLen = snprintf(msg, MAX_LOG_BUF, "%s : %s ", tsPrefix, fdt_log_type2string(severity));

  va_start(list, format);
  vsnprintf(msg + prefixLen, MAX_LOG_BUF - prefixLen, format, list);
  va_end(list);

  printf("%s\n", msg);
}
