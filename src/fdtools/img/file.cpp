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

FdtImageType fdt_img_file_gettype(const char* filename)
{
  FILE *fp = fopen(filename, "rp");
  if (!fp)
    return FDT_IMAGE_TYPE_UNKNOWN;
  
  char sig[FDT_IMAGE_HEADER_SIGNATURE_MAX];
  if (fread(sig, sizeof(char), FDT_IMAGE_HEADER_SIGNATURE_MAX, fp) != FDT_IMAGE_HEADER_SIGNATURE_MAX) {
    return FDT_IMAGE_TYPE_UNKNOWN;
  }

  return FDT_IMAGE_TYPE_UNKNOWN;
}
