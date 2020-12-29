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

bool fdt_d88_image_load(FdtFileImage*, FdtError* err);
bool fdt_d88_image_export(FdtFileImage*, FdtError* err);

FdtImage* fdt_d88_image_new(void)
{
  FdtImage* img = fdt_image_file_new();
  if (!img)
    return NULL;

  fdt_image_settype(img, FDT_IMAGE_TYPE_D88);
  fdt_image_setloader(img, fdt_d88_image_load);
  fdt_image_setexporter(img, fdt_d88_image_export);

  return img;
}
