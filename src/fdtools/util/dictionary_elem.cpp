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

FdtDictionaryElement* fdt_dictionary_element_new()
{
  FdtDictionaryElement* dirElem = (FdtDictionaryElement*)malloc(sizeof(FdtDictionaryElement));
  if (!dirElem)
    return NULL;

  fdt_list_node_init((FdtList*)dirElem);
  dirElem->key = fdt_string_new();
  dirElem->value = fdt_string_new();

  return dirElem;
}

bool fdt_dictionary_element_delete(FdtDictionaryElement* dirElem)
{
  fdt_list_remove((FdtList*)dirElem);

  if (dirElem->key)
    fdt_string_delete(dirElem->key);
  if (dirElem->value)
    fdt_string_delete(dirElem->value);
  free(dirElem);

  return true;
}
