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

#ifndef _FDTOOLS_UTIL_STRING_H_
#define _FDTOOLS_UTIL_STRING_H_

#include <string.h>

#include <fdtools/typedef.h>

#ifdef __cplusplus
extern "C" {
#endif

char* fdt_strdup(const char* str);
size_t fdt_strlen(const char* str);
char* fdt_strcpy(char* dest, const char* src);
char* fdt_strcat(char* dest, const char* src);
int fdt_strcmp(const char* str1, const char* str2);
int fdt_strncmp(const char* str1, const char* str2, size_t nchars);
int fdt_strcasecmp(const char* str1, const char* str2);
bool fdt_streq(const char* str1, const char* str2);
bool fdt_strcaseeq(const char* str1, const char* str2);
ssize_t fdt_strchr(const char* str, const char* chars, size_t nchars);
ssize_t fdt_strrchr(const char* str, const char* chars, size_t nchars);
ssize_t fdt_strstr(const char* haystack, const char* needle);
char* fdt_strtrimwhite(char* str);
char* fdt_strtrim(char* str, char* delim, size_t ndelim);
char* fdt_strltrim(char* str, char* delim, size_t ndelim);
char* fdt_strrtrim(char* str, char* delim, size_t ndelim);
char* fdt_strncpy(char* str1, const char* str2, size_t cnt);
char* fdt_strncat(char* str1, const char* str2, size_t cnt);

const char* fdt_int2str(int value, char* buf, size_t bufSize);
const char* fdt_long2str(long value, char* buf, size_t bufSize);
const char* fdt_float2str(float value, char* buf, size_t bufSize);
const char* fdt_double2str(double value, char* buf, size_t bufSize);
const char* fdt_sizet2str(size_t value, char* buf, size_t bufSize);
const char* fdt_ssizet2str(ssize_t value, char* buf, size_t bufSize);

#define fdt_str2int(value) (value ? atoi(value) : 0)
#define fdt_str2long(value) (value ? atol(value) : 0)
#define fdt_strhex2long(value) (value ? strtol(value, NULL, 16) : 0)
#define fdt_strhex2ulong(value) (value ? strtoul(value, NULL, 16) : 0)
#define fdt_str2float(value) ((float)(value ? atof(value) : 0.0))
#define fdt_str2double(value) (value ? atof(value) : 0.0)
#define fdt_str2sizet(value) ((size_t)(value ? atol(value) : 0))
#define fdt_str2ssizet(value) ((ssize_t)(value ? atol(value) : 0))

typedef struct {
  char* value;
  size_t memSize;
  size_t valueSize;
} FdtString;

FdtString* fdt_string_new();
void fdt_string_delete(FdtString* str);
void fdt_string_clear(FdtString* str);

void fdt_string_setvalue(FdtString* str, const char* value);
void fdt_string_setnvalue(FdtString* str, const char* value, size_t len);
char* fdt_string_getvalue(FdtString* str);
size_t fdt_string_length(FdtString* str);
bool fdt_string_equals(FdtString* str, FdtString* other);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_UTIL_STRING_H_ */
