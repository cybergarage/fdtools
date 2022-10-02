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

typedef bool (*FDT_DICTIONARY_ELEMENT_DESTRUCTORFUNC)(void*);

typedef struct {
  FDT_LIST_STRUCT_MEMBERS
  FdtString* key;
  void* value;
  FDT_DICTIONARY_ELEMENT_DESTRUCTORFUNC destructor;
} FdtDictionaryElement, FdtDictionary;

FdtDictionaryElement* fdt_dictionary_element_new();
bool fdt_dictionary_element_delete(FdtDictionaryElement* elem);
bool fdt_dictionary_element_setvalue(FdtDictionaryElement* elem, void* value, FDT_DICTIONARY_ELEMENT_DESTRUCTORFUNC destructor);

inline void fdt_dictionary_element_setkey(FdtDictionaryElement* elem, const char* name) { fdt_string_setvalue(elem->key, name); }
inline const char* fdt_dictionary_element_getkey(FdtDictionaryElement* elem) { return fdt_string_getvalue(elem->key); }
inline void* fdt_dictionary_element_getvalue(FdtDictionaryElement* elem) { return (elem ? elem->value : NULL); }
inline void fdt_dictionary_element_setdestructor(FdtDictionaryElement* elem, FDT_DICTIONARY_ELEMENT_DESTRUCTORFUNC fn) { elem->destructor = fn; }
inline FDT_DICTIONARY_ELEMENT_DESTRUCTORFUNC fdt_dictionary_element_getdestructor(FdtDictionaryElement* elem) { return elem->destructor; }

inline FdtDictionaryElement* fdt_dictionary_element_next(FdtDictionaryElement* elem) { return (FdtDictionaryElement*)fdt_list_next((FdtListNode*)elem); }
inline void fdt_dictionary_element_remove(FdtDictionaryElement* elem) { fdt_list_remove((FdtListNode*)elem); }

FdtDictionary* fdt_dictionary_new();
bool fdt_dictionary_delete(FdtDictionary* dir);
FdtDictionaryElement* fdt_dictionary_get(FdtDictionary* dir, const char* key);
bool fdt_dictionary_setvalue(FdtDictionary* dir, const char* key, void* value, FDT_DICTIONARY_ELEMENT_DESTRUCTORFUNC destructor);
void* fdt_dictionary_getvalue(FdtDictionary* dir, const char* key);

inline void fdt_dictionary_clear(FdtDictionary* dir) { fdt_list_clear((FdtList*)dir, (FDT_LIST_DESTRUCTORFUNC)fdt_dictionary_element_delete); }
inline size_t fdt_dictionary_size(FdtDictionary* dir) { return fdt_list_size((FdtList*)dir); }
inline FdtDictionaryElement* fdt_dictionary_getelements(FdtDictionary* dir) { return (FdtDictionaryElement*)fdt_list_next((FdtList*)dir); }
inline void fdt_dictionary_add(FdtDictionary* dir, FdtDictionaryElement* elem) { fdt_list_add((FdtList*)dir, (FdtListNode*)elem); }
inline void fdt_dictionary_remove(FdtDictionaryElement* elem) { fdt_list_remove((FdtListNode*)elem); }

bool fdt_dictionary_setstring(FdtDictionary* dir, const char* key, const char* value);
const char* fdt_dictionary_getstring(FdtDictionary* dir, const char* key);

#ifdef __cplusplus

} /* extern "C" */

#endif

#endif
