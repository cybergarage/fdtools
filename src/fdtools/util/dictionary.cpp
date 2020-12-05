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

bool fdt_dictionary_delete(FdtDictionary* dictionaryList)
{
  fdt_dictionary_clear(dictionaryList);
  free(dictionaryList);
  return true;
}

FdtDictionaryElement* fdt_dictionary_getelement(FdtDictionary* dir, const char* key)
{
  FdtDictionaryElement* elem;
  char* elemKey;

  if (!dir || fdt_strlen(key) <= 0)
    return NULL;

  for (elem = fdt_dictionary_gets(dir); elem != NULL; elem = fdt_dictionary_element_next(elem)) {
    elemKey = fdt_dictionary_element_getkey(elem);
    if (fdt_strlen(elemKey) <= 0)
      continue;
    if (fdt_streq(elemKey, key) == true)
      return elem;
  }

  return NULL;
}

bool fdt_dictionary_setvalue(FdtDictionary* dir, const char* key, void *value, FDT_DICTIONARY_ELEMENT_DESTRUCTORFUNC destructor)
{
  FdtDictionaryElement* elem = fdt_dictionary_getelement(dir, key);
  if (!elem) {
    elem = fdt_dictionary_element_new();
    if (!elem)
      return false;
    fdt_dictionary_add(dir, elem);
  }

  fdt_dictionary_element_setkey(elem, key);
  fdt_dictionary_element_setvalue(elem, value);
  fdt_dictionary_element_setdestructor(elem, destructor);

  return true;
}

void *fdt_dictionary_getvalue(FdtDictionary* dir, const char* key)
{
  FdtDictionaryElement* elem;

  elem = fdt_dictionary_getelement(dir, key);
  if (!elem)
    return NULL;

  return fdt_dictionary_element_getvalue(elem);
}
