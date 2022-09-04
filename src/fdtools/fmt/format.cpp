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

#include <fdtools/fmt/format.h>

FdtFormat* fdt_format_new()
{
  FdtFormat* fmt = (FdtFormat*)calloc(sizeof(FdtFormat), 1);
  if (!fmt) {
    return NULL;
  }

  if (!fdt_format_init(fmt)) {
    fdt_format_delete(fmt);
    return NULL;
  }

  return fmt;
}

bool fdt_format_init(FdtFormat* fmt)
{
  return true;
}

bool fdt_format_delete(FdtFormat* fmt)
{
  if (fmt->image_destructor)
    return fmt->image_destructor(fmt);
  free(fmt);
  return true;
}

FdtFormatType fdt_format_gettype(FdtFormat* fmt)
{
  if (!fmt || !fmt->image_gettype)
    return FDT_FORMAT_TYPE_UNKNOWN;
  return fmt->image_gettype(fmt);
}

const char* fdt_format_gettypeid(FdtFormat* fmt)
{
  if (!fmt || !fmt->image_gettypeid)
    return "";
  return fmt->image_gettypeid(fmt);
}
