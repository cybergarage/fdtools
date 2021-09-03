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

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <fdtools/typedef.h>
#include <fdtools/util/string.h>

char* fdt_strdup(const char* str)
{
  if (!str)
    return NULL;

#if defined(HAVE_STRDUP)
  return strdup(str);
#else
  char* cpStrBuf = (char*)malloc(strlen(str) + 1);
  if (NULL != cpStrBuf)
    strcpy(cpStrBuf, str);
  return cpStrBuf;
#endif
}

size_t fdt_strlen(const char* str)
{
  return (!str) ? 0 : strlen(str);
}

char* fdt_strcpy(char* dest, const char* src)
{
  if (!dest || !src)
    return dest;
  return strcpy(dest, src);
}

char* fdt_strcat(char* dest, const char* src)
{
  if (!dest || !src)
    return dest;
  return strcat(dest, src);
}

int fdt_strcmp(const char* str1, const char* str2)
{
  if (!str1)
    return -1;
  if (!str2)
    return 1;
  return strcmp(str1, str2);
}

int fdt_strncmp(const char* str1, const char* str2, size_t nchars)
{
  if (!str1)
    return -1;
  if (!str2)
    return 1;
  return strncmp(str1, str2, nchars);
}

int fdt_strcasecmp(const char* str1, const char* str2)
{
  if (!str1 || !str2)
    return -1;
#if !defined(WIN32)
  return strcasecmp(str1, str2);
#else
  for (; toupper(*str1) == toupper(*str2); str1++, str2++) {
    if (*str1 == '\0')
      return 0;
  }
  return *str1 - *str2;
#endif
}

bool fdt_streq(const char* str1, const char* str2)
{
  if (!str1 || !str2)
    return false;
  return ((fdt_strcmp(str1, str2) == 0) ? true : false);
}

bool fdt_strcaseeq(const char* str1, const char* str2)
{
  if (!str1 || !str2)
    return false;
  return ((fdt_strcasecmp(str1, str2) == 0) ? true : false);
}

ssize_t fdt_strstr(const char* haystack, const char* needle)
{
  if (!haystack || !needle)
    return -1;
  const char* strPos = strstr(haystack, needle);
  if (!strPos)
    return -1;
  return (strPos - haystack);
}

ssize_t fdt_strchr(const char* str, const char* chars, size_t nchars)
{
  if (!str || !chars)
    return -1;
  size_t strLen = fdt_strlen(str);
  for (ssize_t i = 0; i < strLen; i++) {
    for (ssize_t j = 0; j < nchars; j++) {
      if (str[i] == chars[j])
        return i;
    }
  }
  return -1;
}

ssize_t fdt_strrchr(const char* str, const char* chars, size_t nchars)
{
  if (!str || !chars)
    return -1;
  size_t strLen = fdt_strlen(str);
  for (ssize_t i = (strLen - 1); 0 <= i; i--) {
    for (ssize_t j = 0; j < nchars; j++) {
      if (str[i] == chars[j])
        return i;
    }
  }
  return -1;
}

char* fdt_strtrimspaces(char* str)
{
  size_t strLen = fdt_strlen(str);
  if (strLen == 0)
    return str;
  ssize_t i;
  for (i = (strLen - 1); 0 <= i; i--) {
    if (isspace(str[i])) {
      strLen--;
    }
  }
  for (i = 0; i < strLen; i++) {
    if (!isspace(str[i]))
      break;
  }
  if (i > 0)
    memmove(str, str + i, strLen - i);
  str[strLen] = 0;
  return str;
}

char* fdt_strtrim(char* str, char* delim, size_t ndelim)
{
  if (!str || !delim)
    return NULL;
  fdt_strrtrim(str, delim, ndelim);
  return fdt_strltrim(str, delim, ndelim);
}

char* fdt_strltrim(char* str, char* delim, size_t ndelim)
{
  size_t strLen = fdt_strlen(str);
  for (ssize_t i = 0; i < strLen; i++) {
    bool hasDelim = false;
    for (ssize_t j = 0; j < ndelim; j++) {
      if (str[i] == delim[j]) {
        hasDelim = true;
        break;
      }
    }
    if (hasDelim == false)
      return (str + i);
  }
  return (str + strLen);
}

char* fdt_strrtrim(char* str, char* delim, size_t ndelim)
{
  size_t strLen = fdt_strlen(str);
  for (ssize_t i = (strLen - 1); 0 <= i; i--) {
    bool hasDelim = false;
    for (ssize_t j = 0; j < ndelim; j++) {
      if (str[i] == delim[j]) {
        hasDelim = true;
        str[i] = '\0';
        break;
      }
    }
    if (hasDelim == false)
      break;
  }
  return str;
}

char* fdt_strncpy(char* dest, const char* src, size_t cnt)
{
  if (!dest || !src || (cnt == 0))
    return dest;
  return strncpy(dest, src, cnt);
}

char* fdt_strncat(char* dest, const char* src, size_t cnt)
{
  size_t destLen = fdt_strlen(dest);
  return fdt_strncpy((dest + destLen), src, cnt);
}

const char* fdt_int2str(int value, char* buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
  snprintf(buf, bufSize, "%d", value);
#else
  sprintf(buf, "%d", value);
#endif
  return buf;
}

const char* fdt_long2str(long value, char* buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
  snprintf(buf, bufSize, "%ld", value);
#else
  sprintf(buf, "%ld", value);
#endif
  return buf;
}

const char* fdt_float2str(float value, char* buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
  snprintf(buf, bufSize, "%f", value);
#else
  sprintf(buf, "%f", value);
#endif
  return buf;
}

const char* fdt_double2str(double value, char* buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
  snprintf(buf, bufSize, "%lf", value);
#else
  sprintf(buf, "%lf", value);
#endif
  return buf;
}

const char* fdt_sizet2str(size_t value, char* buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
  snprintf(buf, bufSize, "%zd", value);
#else
  sprintf(buf, "%zd", value);
#endif
  return buf;
}

const char* fdt_ssizet2str(ssize_t value, char* buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
  snprintf(buf, bufSize, "%zd", value);
#else
  sprintf(buf, "%zd", value);
#endif
  return buf;
}
