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

FdtFormatPlugins* fdt_format_plugins_new()
{
  FdtFormatPlugin* plgs = (FdtFormatPlugins*)malloc(sizeof(FdtFormatPlugins));
  if (!plgs) {
    return NULL;
  }
  fdt_list_header_init((FdtList*)plgs);
  return plgs;
}

bool fdt_format_plugins_delete(FdtFormatPlugins* plgs)
{
  if (!plgs)
    return true;
  fdt_format_plugins_clear(plgs);
  free(plgs);
  return true;
}

bool fdt_format_plugins_add(FdtFormatPlugins* plgs, FDT_FORMAT_FORMATTER fn)
{
  FdtFormatPlugin* plg = fdt_format_plugin_new();
  if (!plg)
    return false;
  fdt_format_plugin_setformatter(plg, fn);
  fdt_list_add((FdtList*)plgs, (FdtListNode*)plg);
  return true;
}
