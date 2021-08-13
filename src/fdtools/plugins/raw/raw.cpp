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

#include <fdtools/plugins/raw/raw.h>

FdtImage* fdt_raw_image_new(void)
{
  FdtImage* img = fdt_image_file_new();
  if (!img)
    return NULL;

  fdt_image_setgettypeid(img, fdt_raw_image_gettypeid);
  fdt_image_sethasext(img, fdt_raw_image_hasext);
  fdt_image_setloader(img, fdt_raw_image_load);
  fdt_image_setexporter(img, fdt_raw_image_export);

  return img;
}

const char* fdt_raw_image_gettypeid(FdtImage* img)
{
  return "RAW";
}

bool fdt_raw_image_hasext(FdtFileImage* img, const char* filename)
{
  if (fdt_file_hasextension(filename, FDT_RAW_EXTENTION_RAW))
    return true;
  if (fdt_file_hasextension(filename, FDT_RAW_EXTENTION_IMG))
    return true;
  return false;
}
