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

  fmt->type = FDT_FORMAT_TYPE_UNKNOWN;

  return fmt;
}

bool fdt_format_delete(FdtFormat* fmt)
{
  if (fmt->format_destructor)
    return fmt->format_destructor(fmt);
  free(fmt);
  return true;
}

FdtFormatType fdt_format_gettype(FdtFormat* fmt)
{
  if (!fmt)
    return FDT_FORMAT_TYPE_UNKNOWN;
  return fmt->type;
}

const char* fdt_format_gettypeid(FdtFormat* fmt)
{
  if (!fmt || !fmt->format_gettypeid)
    return "";
  return fmt->format_gettypeid(fmt);
}

bool fdt_format_format(FdtFormat* fmt, FdtError* err)
{
  if (!fmt || !fmt->image) {
    fdt_error_setmessage(err, FDT_FORMAT_ERROR_NO_IMAGE);
    return false;
  }
  if (!fmt->format_format) {
    fdt_error_setmessage(err, FDT_FORMAT_ERROR_INVALID_OPERATION, "format");
    return false;
  }
  return fmt->format_format(fmt, err);
}

bool fdt_format_list(FdtFormat* fmt, FdtFiles* files, FdtError* err)
{
  if (!fmt || !fmt->image) {
    fdt_error_setmessage(err, FDT_FORMAT_ERROR_NO_IMAGE);
    return false;
  }
  if (!fmt->format_list) {
    fdt_error_setmessage(err, FDT_FORMAT_ERROR_INVALID_OPERATION, "list");
    return false;
  }
  return fmt->format_list(fmt, files, err);
}

bool fdt_format_add(FdtFormat* fmt, FdtFile* file, FdtError* err)
{
  if (!fmt || !fmt->image) {
    fdt_error_setmessage(err, FDT_FORMAT_ERROR_NO_IMAGE);
    return false;
  }
  if (!fmt->format_add) {
    fdt_error_setmessage(err, FDT_FORMAT_ERROR_INVALID_OPERATION, "add");
    return false;
  }
  return fmt->format_add(fmt, file, err);
}

bool fdt_format_del(FdtFormat* fmt, FdtFile* file, FdtError* err)
{
  if (!fmt || !fmt->image) {
    fdt_error_setmessage(err, FDT_FORMAT_ERROR_NO_IMAGE);
    return false;
  }
  if (!fmt->format_del) {
    fdt_error_setmessage(err, FDT_FORMAT_ERROR_INVALID_OPERATION, "del");
    return false;
  }
  return fmt->format_del(fmt, file, err);
}
