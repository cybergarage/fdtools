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

#include <fdtools/util/dictionary.h>

FdtDictionary* fdt_dictionary_new()
{
  FdtDictionary* dir;

  dir = (FdtDictionary*)malloc(sizeof(FdtDictionary));
  if (!dir) {
    return NULL;
  }

  fdt_list_header_init((FdtList*)dir);
  dir->key = NULL;
  dir->value = NULL;

  return dir;
}

bool fdt_dictionary_delete(FdtDictionary* dir)
{
  if (!dir)
    return false;
  fdt_dictionary_clear(dir);
  free(dir);
  return true;
}

FdtDictionaryElement* fdt_dictionary_get(FdtDictionary* dir, const char* key)
{
  if (!dir || fdt_strlen(key) <= 0)
    return NULL;

  for (FdtDictionaryElement* elem = fdt_dictionary_gets(dir); elem != NULL; elem = fdt_dictionary_element_next(elem)) {
    const char* elemKey = fdt_dictionary_element_getkey(elem);
    if (fdt_strlen(elemKey) <= 0)
      continue;
    if (fdt_streq(elemKey, key) == true)
      return elem;
  }

  return NULL;
}

bool fdt_dictionary_setvalue(FdtDictionary* dir, const char* key, void* value, FDT_DICTIONARY_ELEMENT_DESTRUCTORFUNC destructor)
{
  FdtDictionaryElement* elem = fdt_dictionary_get(dir, key);
  if (!elem) {
    elem = fdt_dictionary_element_new();
    if (!elem)
      return false;
    fdt_dictionary_add(dir, elem);
  }

  fdt_dictionary_element_setkey(elem, key);
  fdt_dictionary_element_setvalue(elem, value, destructor);
  fdt_dictionary_element_setdestructor(elem, destructor);

  return true;
}

void* fdt_dictionary_getvalue(FdtDictionary* dir, const char* key)
{
  if (!dir)
    return NULL;

  FdtDictionaryElement* elem = fdt_dictionary_get(dir, key);
  if (!elem)
    return NULL;

  return fdt_dictionary_element_getvalue(elem);
}

bool fdt_dictionary_setstring(FdtDictionary* dir, const char* key, const char* value)
{
  FdtString* str = fdt_string_new();
  if (!str)
    return false;
  fdt_string_setvalue(str, value);
  return fdt_dictionary_setvalue(dir, key, str, (FDT_DICTIONARY_ELEMENT_DESTRUCTORFUNC)fdt_string_delete);
}

const char* fdt_dictionary_getstring(FdtDictionary* dir, const char* key)
{
  if (!dir)
    return NULL;
  void* str = fdt_dictionary_getvalue(dir, key);
  if (!str)
    return NULL;
  return fdt_string_getvalue((FdtString*)str);
}
