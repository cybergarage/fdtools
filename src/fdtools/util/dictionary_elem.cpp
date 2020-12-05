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
  FdtDictionaryElement* elem = (FdtDictionaryElement*)malloc(sizeof(FdtDictionaryElement));
  if (!elem)
    return NULL;

  fdt_list_node_init((FdtList*)elem);
  elem->key = fdt_string_new();
  elem->value = NULL;
  elem->destructor = NULL;

  return elem;
}

bool fdt_dictionary_element_delete(FdtDictionaryElement* elem)
{
  fdt_list_remove((FdtList*)elem);

  if (elem->key) {
    fdt_string_delete(elem->key);
  }
  if (elem->value || elem->destructor) {
    elem->destructor(elem->value);
  }

  free(elem);

  return true;
}
