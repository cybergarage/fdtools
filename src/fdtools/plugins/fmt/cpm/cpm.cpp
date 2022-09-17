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

FdtFormat* fdt_cpm_format_new(void)
{
  FdtFormat* fmt = fdt_format_new();
  if (!fmt)
    return NULL;

  fmt->type = FDT_FORMAT_TYPE_CPM;
  fdt_format_setgettypeid(fmt, fdt_cpm_format_gettypeid);

  return fmt;
}

const char* fdt_cpm_format_gettypeid(FdtFormat* fmt)
{
  return "RAW";
}
