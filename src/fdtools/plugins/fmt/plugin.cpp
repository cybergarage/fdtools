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

#include <fdtools/plugins/fmt/plugin.h>

FdtFormatPlugin* fdt_format_plugin_new()
{
  FdtFormatPlugin* plg = (FdtFormatPlugin*)malloc(sizeof(FdtFormatPlugin));
  if (!plg) {
    return NULL;
  }

  fdt_list_node_init((FdtListNode*)plg);

  return plg;
}

bool fdt_format_plugin_delete(FdtFormatPlugin* plg)
{
  if (!plg)
    return true;
  fdt_list_remove((FdtListNode*)plg);
  free(plg);
  return true;
}
