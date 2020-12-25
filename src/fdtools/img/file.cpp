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
#include <fdtools/img/file.h>
#include <fdtools/img/hfe.h>
#include <fdtools/util/string.h>

FdtImageType fdt_img_file_gettype(const char* filename)
{
  FILE* fp = fdt_file_open(filename, FDT_FILE_READ);
  if (!fp)
    return FDT_IMAGE_TYPE_UNKNOWN;

  char sig[FDT_IMAGE_HEADER_SIGNATURE_MAX];
  size_t n_read = fread(sig, sizeof(char), FDT_IMAGE_HEADER_SIGNATURE_MAX, fp);
  fdt_file_close(fp);

  // Identify image file type by the header signature

  if (n_read != FDT_IMAGE_HEADER_SIGNATURE_MAX) {
    return FDT_IMAGE_TYPE_UNKNOWN;
  }

  if (fdt_strncmp(sig, HFE_IMAGE_HEADER_SIGNATURE, fdt_strlen(HFE_IMAGE_HEADER_SIGNATURE)) == 0) {
    return FDT_IMAGE_TYPE_HFE;
  }

  // Identify image file type by the filename extention

  if (fdt_file_hasextension(filename, D88_EXTENTION_D88))
    return FDT_IMAGE_TYPE_D88;
  if (fdt_file_hasextension(filename, D88_EXTENTION_88D))
    return FDT_IMAGE_TYPE_D88;
  if (fdt_file_hasextension(filename, D88_EXTENTION_D77))
    return FDT_IMAGE_TYPE_D88;
  if (fdt_file_hasextension(filename, D88_EXTENTION_D68))
    return FDT_IMAGE_TYPE_D88;
  if (fdt_file_hasextension(filename, D88_EXTENTION_D98))
    return FDT_IMAGE_TYPE_D88;
  if (fdt_file_hasextension(filename, D88_EXTENTION_D8U))
    return FDT_IMAGE_TYPE_D88;
  if (fdt_file_hasextension(filename, D88_EXTENTION_1DD))
    return FDT_IMAGE_TYPE_D88;

  return FDT_IMAGE_TYPE_UNKNOWN;
}
