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

static int fdt_log_level = FDT_LOG_NONE;

static const char* fdt_log_type2string(int type)
{
  switch (type) {
  case FDT_LOG_ERROR:
    return FDT_LOG_ERROR_PREFIX;
    break;

  case FDT_LOG_WARN:
    return FDT_LOG_WARN_PREFIX;
    break;

  case FDT_LOG_INFO:
    return FDT_LOG_INFO_PREFIX;
    break;

  case FDT_LOG_DEBUG:
    return FDT_LOG_DEBUG_PREFIX;
    break;
  }

  return "";
}

void fdt_log_setlevel(int level)
{
  fdt_log_level = level;
}

void fdt_log_output(int level, const char* file, int line_n, const char* function, const char* format, ...)
{
  if (fdt_log_level < level)
    return;

  va_list list;

  char msg[MAX_LOG_BUF], tsPrefix[MAX_LOG_BUF];
  time_t ts;
  struct tm* localts;
  size_t prefixLen = -1;

  ts = time(NULL);
  localts = localtime(&ts);

  strftime(tsPrefix, MAX_LOG_BUF, "%c", localts);

  prefixLen = snprintf(msg, MAX_LOG_BUF, "%s : %s ", tsPrefix, fdt_log_type2string(level));

  va_start(list, format);
  vsnprintf(msg + prefixLen, MAX_LOG_BUF - prefixLen, format, list);
  va_end(list);

  printf("%s\n", msg);
}
