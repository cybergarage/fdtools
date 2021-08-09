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

#include <fdtools/plugins/loader.h>
#include <fdtools/plugins/raw/raw.h>

#include <fdtools/plugins/d88/d88.h>

FdtImagePlugins* fdt_plugins_getallimagers()
{
  FdtImagePlugin* plgs = fdt_image_plugin_new();

  // Adds your image plugins

  fdt_image_plugins_add(plgs, fdt_d88_image_new);

  // Adds the raw image plugin because the plugin has no file header

  fdt_image_plugins_add(plgs, fdt_raw_image_new);

  return plgs;
}
