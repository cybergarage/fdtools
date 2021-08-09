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

#include <fdtools/img/plugin.h>

FdtImagePlugin* fdt_image_plugin_new()
{
  FdtImagePlugin* plg = (FdtImagePlugin*)calloc(sizeof(FdtImagePlugin), 1);
  if (!plg) {
    return NULL;
  }
  plg->imagers = fdt_dictionary_new();
  return plg;
}

bool fdt_image_plugin_delete(FdtImagePlugin *plg)
{
  fdt_dictionary_delete(plg->imagers);
  free(plg);
  return true;
}
