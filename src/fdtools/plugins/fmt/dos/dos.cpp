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

#include <fdtools/plugins/fmt/dos/dos.h>
#include <fdtools/plugins/fmt/dos/sector.h>

FdtFormat* fdt_dos_new(void)
{
  FdtFormat* fmt = fdt_format_new();
  if (!fmt)
    return NULL;

  fmt->type = FDT_FORMAT_TYPE_DOS;

  fdt_format_setgettypeid(fmt, fdt_dos_gettypeid);
  fdt_format_setformat(fmt, fdt_dos_format);
  fdt_format_setlist(fmt, fdt_dos_list);
  fdt_format_setadd(fmt, fdt_dos_add);
  fdt_format_setdel(fmt, fdt_dos_del);

  return fmt;
}

FdtFormat* fdt_dos_from(FdtImage* img, FdtError* err)
{
  FdtFormat* fmt = fdt_dos_new();
  if (!fmt) {
    return NULL;
  }

  fdt_format_setimage(fmt, img);

  return fmt;
}

const char* fdt_dos_gettypeid(FdtFormat* fmt)
{
  return "DOS";
}

bool fdt_dos_format(FdtFormat* fmt, FdtError* err)
{
  FdtImage* img = fdt_format_getimage(fmt);
  if (!img) {
    return false;
  }

  if (fdt_image_getnsectors(img) == 0) {
    if (!fdt_image_generatesectors(img, err))
      return false;
  }

  if (!fdt_dos_formatbootsector(fmt, err))
    return false;

  return true;
}

bool fdt_dos_list(FdtFormat* fmt, FdtFiles* files, FdtError* err)
{
  return false;
}

bool fdt_dos_add(FdtFormat* fmt, FdtFile* file, FdtError* err)
{
  return false;
}

bool fdt_dos_del(FdtFormat* fmt, FdtFile* file, FdtError* err)
{
  return false;
}
