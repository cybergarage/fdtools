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
#include <fdtools/util/list.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////
// fdt_str*
////////////////////////////////////////

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
char* fdt_strtrimspaces(char* str);
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

inline int fdt_str2int(const char* value) { return (value ? atoi(value) : 0); }
inline long fdt_str2long(const char* value) { return (value ? atol(value) : 0); }
inline long fdt_strhex2long(const char* value) { return (value ? strtol(value, NULL, 16) : 0); }
inline unsigned long fdt_strhex2ulong(const char* value) { return (value ? strtoul(value, NULL, 16) : 0); }
inline float fdt_str2float(const char* value) { return ((float)(value ? atof(value) : 0.0)); }
inline double fdt_str2double(const char* value) { return (value ? atof(value) : 0.0); }
inline size_t fdt_str2sizet(const char* value) { return ((size_t)(value ? atol(value) : 0)); }
inline size_t fdt_str2ssizet(const char* value) { return ((ssize_t)(value ? atol(value) : 0)); }

////////////////////////////////////////
// fdt_string_*
////////////////////////////////////////

typedef struct {
  FDT_LIST_STRUCT_MEMBERS
  char* value;
  size_t mem_size;
  size_t value_size;
} FdtString, FdtStrings;

FdtString* fdt_string_new();
bool fdt_string_delete(FdtString* str);
bool fdt_string_clear(FdtString* str);

void fdt_string_setvalue(FdtString* str, const char* value);
void fdt_string_setnvalue(FdtString* str, const char* value, size_t len);
void fdt_string_setvaluef(FdtString* str, const char* format, ...);
bool fdt_string_appendvalue(FdtString* str, const char* value);
bool fdt_string_appendnvalue(FdtString* str, const char* value, size_t valueLen);
const char* fdt_string_getvalue(FdtString* str);
bool fdt_string_equals(FdtString* str, FdtString* other);
size_t fdt_string_length(FdtString* str);

////////////////////////////////////////
// fdt_strings_*
////////////////////////////////////////

FdtStrings* fdt_strings_new();
void fdt_strings_delete(FdtStrings*);

inline FdtString* fdt_string_next(FdtString* str) { return (FdtString*)fdt_list_next((FdtListNode*)str); }

inline size_t fdt_strings_size(FdtString* strs) { return fdt_list_size((FdtList*)strs); }
inline FdtString* fdt_strings_gets(FdtString* strs) { return (FdtString*)fdt_list_gets((FdtList*)strs); }
inline void fdt_strings_addstring(FdtString* strs, FdtString* str) { fdt_list_add((FdtList*)strs, (FdtListNode*)str); }
inline void fdt_strings_clear(FdtString* strs) { fdt_list_clear((FdtList*)strs, (FDT_LIST_DESTRUCTORFUNC)fdt_string_delete); }

void fdt_strings_addcstring(FdtStrings*, const char* value);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_UTIL_STRING_H_ */
