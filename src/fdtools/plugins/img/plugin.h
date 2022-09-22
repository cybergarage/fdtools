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

#ifndef _FDTOOLS_PLUGINS_IMAGE_H_
#define _FDTOOLS_PLUGINS_IMAGE_H_

#include <fdtools/img/image.h>
#include <fdtools/util/list.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
  FDT_LIST_STRUCT_MEMBERS
  FDT_IMAGE_IMAGER imager;
} FdtImagePlugin, FdtImagePlugins;

FdtImagePlugins* fdt_image_plugins_new();
bool fdt_image_plugins_delete(FdtImagePlugins*);
bool fdt_image_plugins_add(FdtImagePlugins*, FDT_IMAGE_IMAGER);

#define fdt_image_plugins_size(plgs) fdt_list_size((FdtList*)plgs)
#define fdt_image_plugins_gets(plgs) ((FdtImagePlugin*)fdt_list_gets((FdtList*)plgs))
#define fdt_image_plugins_get(plgs, n) ((FdtImagePlugin*)fdt_list_get((FdtList*)plgs, n))
#define fdt_image_plugins_clear(plgs) fdt_list_clear((FdtList*)plgs, (FDT_LIST_DESTRUCTORFUNC)fdt_image_plugin_delete)

FdtImagePlugin* fdt_image_plugin_new();
bool fdt_image_plugin_delete(FdtImagePlugin*);

#define fdt_image_plugin_setimager(plg, v) (plg->imager = v)
#define fdt_image_plugin_getimager(plg) (plg->imager)
#define fdt_image_plugin_createimage(plg) (plg->imager())
#define fdt_image_plugin_next(plg) (FdtImagePlugin*)fdt_list_next((FdtListNode*)plg)

void fdt_image_plugins_getallextentions(FdtStrings*);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_PLUGINS_IMAGE_H_ */
