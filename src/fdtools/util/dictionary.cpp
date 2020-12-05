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

void fdt_dictionary_delete(FdtDictionary* dictionaryList)
{
  fdt_dictionary_clear(dictionaryList);
  free(dictionaryList);
}

FdtDictionaryElement* fdt_dictionary_getelement(FdtDictionary* dir, const char* key)
{
  FdtDictionaryElement* dirElem;
  char* dirElemKey;

  if (!dir || fdt_strlen(key) <= 0)
    return NULL;

  for (dirElem = fdt_dictionary_gets(dir); dirElem != NULL; dirElem = fdt_dictionary_element_next(dirElem)) {
    dirElemKey = fdt_dictionary_element_getkey(dirElem);
    if (fdt_strlen(dirElemKey) <= 0)
      continue;
    if (fdt_streq(dirElemKey, key) == true)
      return dirElem;
  }

  return NULL;
}

bool fdt_dictionary_setvalue(FdtDictionary* dir, const char* key, const char* value)
{
  FdtDictionaryElement* dirElem = fdt_dictionary_getelement(dir, key);
  if (!dirElem) {
    dirElem = fdt_dictionary_element_new();
    if (!dirElem)
      return false;
    fdt_dictionary_add(dir, dirElem);
  }

  fdt_dictionary_element_setkey(dirElem, key);
  fdt_dictionary_element_setvalue(dirElem, value);

  return true;
}

const char* fdt_dictionary_getvalue(FdtDictionary* dir, const char* key)
{
  FdtDictionaryElement* dirElem;

  dirElem = fdt_dictionary_getelement(dir, key);
  if (!dirElem)
    return NULL;

  return fdt_dictionary_element_getvalue(dirElem);
}
