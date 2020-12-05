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

#ifndef _FDTOOLS_UTIL_DICTIONARY_H_
#define _FDTOOLS_UTIL_DICTIONARY_H_

#include <fdtools/typedef.h>
#include <fdtools/util/list.h>
#include <fdtools/util/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  FDT_LIST_STRUCT_MEMBERS
  FdtString* key;
  FdtString* value;
} FdtDictionaryElement, FdtDictionary;

FdtDictionaryElement* fdt_dictionary_element_new();
bool fdt_dictionary_element_delete(FdtDictionaryElement* dirElem);

#define fdt_dictionary_element_setkey(dirElem, name) fdt_string_setvalue(dirElem->key, name)
#define fdt_dictionary_element_getkey(dirElem) fdt_string_getvalue(dirElem->key)
#define fdt_dictionary_element_setvalue(dirElem, val) fdt_string_setvalue(dirElem->value, val)
#define fdt_dictionary_element_getvalue(dirElem) fdt_string_getvalue(dirElem->value)

#define fdt_dictionary_element_next(dirElem) (FdtDictionaryElement*)fdt_list_next((FdtList*)dirElem)
#define fdt_dictionary_element_remove(dirElem) fdt_list_remove((FdtList*)dirElem)

FdtDictionary* fdt_dictionary_new();
void fdt_dictionary_delete(FdtDictionary* dir);

#define fdt_dictionary_clear(dir) fdt_list_clear((FdtList*)dir, (FDT_LIST_DESTRUCTORFUNC)fdt_dictionary_element_delete)
#define fdt_dictionary_size(dir) fdt_list_size((FdtList*)dir)
#define fdt_dictionary_gets(dir) (FdtDictionaryElement*)fdt_list_next((FdtList*)dir)
#define fdt_dictionary_add(dir, dirElem) fdt_list_add((FdtList*)dir, (FdtList*)dirElem)
#define fdt_dictionary_remove(dirElem) fdt_list_remove((FdtList*)dirElem)

FdtDictionaryElement* fdt_dictionary_get(FdtDictionary* dir, const char* key);
void fdt_dictionary_setvalue(FdtDictionary* dir, const char* key, const char* value);
const char* fdt_dictionary_getvalue(FdtDictionary* dir, const char* key);

#ifdef __cplusplus

} /* extern "C" */

#endif

#endif
