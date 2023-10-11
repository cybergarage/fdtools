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

#include <fdtools/plugins/fmt/x68/x68.h>

FdtFormat* fdt_x68_format_new(void)
{
  FdtFormat* fmt = fdt_format_new();
  if (!fmt)
    return NULL;

  fmt->type = FDT_FORMAT_TYPE_DOS;

  fdt_format_setgettypeid(fmt, fdt_x68_format_gettypeid);
  fdt_format_setformat(fmt, fdt_x68_format_format);
  fdt_format_setlist(fmt, fdt_x68_format_list);
  fdt_format_setadd(fmt, fdt_x68_format_add);
  fdt_format_setdel(fmt, fdt_x68_format_del);

  return fmt;
}

const char* fdt_x68_format_gettypeid(FdtFormat* fmt)
{
  return "X68000";
}

bool fdt_x68_format_format(FdtFormat* fmt)
{
  return false;
}

bool fdt_x68_format_list(FdtFormat* fmt, FdtFiles* files)
{
  return false;
}

bool fdt_x68_format_add(FdtFormat* fmt, FdtFile* file)
{
  return false;
}

bool fdt_x68_format_del(FdtFormat* fmt, FdtFile* file)
{
  return false;
}

bool fdt_x68_format_loadimage(FdtImage*, FdtError*)
{
  return false;
}
