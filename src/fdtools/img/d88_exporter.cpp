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

#include <fdtools/img/d88.h>
#include <fdtools/util/file.h>
#include <fdtools/util/string.h>

bool fdt_d88_header_setconfig(FdtD88Header *d88header, FdtImage* img);

bool fdt_d88_image_export(FdtImage* img, FILE* fp)
{
  FdtD88Header d88_header;
  if (!fdt_d88_header_setconfig(&d88_header, img))
    return false;
  return true;
}

bool fdt_d88_header_setconfig(FdtD88Header *d88header, FdtImage* img)
{
  memset(d88header, 0, sizeof(FdtD88Header));
  
  fdt_strncpy(d88header->name, fdt_image_getname(img), D88_NAME_MAXLEN);
  d88header->write_protect = fdt_image_getwriteprotect(img) ? D88_WRITE_PROTECT_ENABLED : D88_WRITE_PROTECT_NONE;
  
  return true;
}
