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

#ifndef _FDTOOLS_PLUGINS_FORMAT_H_
#define _FDTOOLS_PLUGINS_FORMAT_H_

#include <fdtools/fmt/format.h>
#include <fdtools/util/list.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
  FDT_LIST_STRUCT_MEMBERS
  FDT_FORMAT_FORMATTER imager;
} FdtFormatPlugin, FdtFormatPlugins;

FdtFormatPlugins* fdt_format_plugins_new();
bool fdt_format_plugins_delete(FdtFormatPlugins*);
bool fdt_format_plugins_add(FdtFormatPlugins*, FDT_FORMAT_FORMATTER);

#define fdt_format_plugins_size(plgs) fdt_list_size((FdtList*)plgs)
#define fdt_format_plugins_gets(plgs) ((FdtFormatPlugin*)fdt_list_gets((FdtList*)plgs))
#define fdt_format_plugins_get(plgs, n) ((FdtFormatPlugin*)fdt_list_get((FdtList*)plgs, n))
#define fdt_format_plugins_clear(plgs) fdt_list_clear((FdtList*)plgs, (FDT_LIST_DESTRUCTORFUNC)fdt_format_plugin_delete)

FdtFormatPlugin* fdt_format_plugin_new();
bool fdt_format_plugin_delete(FdtFormatPlugin*);

#define fdt_format_plugin_setformatter(plg, v) (plg->imager = v)
#define fdt_format_plugin_getformatter(plg) (plg->imager)
#define fdt_format_plugin_next(plg) (FdtFormatPlugin*)fdt_list_next((FdtListNode*)plg)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_PLUGINS_FORMAT_H_ */
