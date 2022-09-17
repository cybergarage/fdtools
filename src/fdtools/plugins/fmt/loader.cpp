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

#include <fdtools/plugins/fmt/cpm/cpm.h>
#include <fdtools/plugins/fmt/dos/dos.h>
#include <fdtools/plugins/fmt/loader.h>

static FdtFormatPlugins* fmt_plgs;

FdtFormatPlugins* fdt_format_plugins_getfomatters()
{
  if (fmt_plgs)
    return fdt_format_plugin_next(fmt_plgs);

  fmt_plgs = fdt_format_plugins_new();

  // Adds your new format plugins
  fdt_format_plugins_add(fmt_plgs, fdt_dos_format_new);
  fdt_format_plugins_add(fmt_plgs, fdt_cpm_format_new);

  return fdt_format_plugin_next(fmt_plgs);
}
