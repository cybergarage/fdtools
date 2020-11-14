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

#include <stdio.h>
#include <string.h>

#include <fdtools/img/file.h>
#include <fdtools/util/string.h>

FdtHfeHeader* fdt_img_hfe_header_new(void)
{
  FdtHfeHeader* header = (FdtHfeHeader*)malloc(sizeof(FdtHfeHeader));
  if (!header) {
    return NULL;
  }
  fdt_image_header_init((FdtImageHeader*)header);
  return header;
}

bool fdt_img_hfe_header_load(FdtHfeHeader* header, FILE* fp)
{
  byte header_buf[sizeof(HFE_FILE_FORMAT_HEADER)];
  if (!fdt_img_file_read(fp, header_buf, sizeof(header_buf)))
    return false;
  return fdt_img_hfe_header_parse(header, header_buf);
}

bool fdt_img_hfe_header_parse(FdtHfeHeader*, byte*)
{
  return false;
}
