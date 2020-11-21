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

FILE* fdt_img_file_open(const char* filename)
{
  return fopen(filename, "rb");
}

int fdt_img_file_close(FILE* fp)
{
  return fclose(fp);
}

bool fdt_img_file_read(FILE* fp, byte* buf, size_t n)
{
  return (fread(buf, 1, n, fp) == n) ? true : false;
}

bool fdt_img_file_hasextension(const char* filename, const char *extname)
{
  size_t filename_len = fdt_strlen(filename);
  size_t extname_len = fdt_strlen(extname);
  if (filename_len < extname_len)
    return false;
  size_t filename_ext_idx = filename_len - extname_len - 1;
  return (fdt_strcmp((filename + filename_ext_idx), extname) == 0) ? true : false;
}

FdtImageType fdt_img_file_gettype(const char* filename)
{
  FILE* fp = fdt_img_file_open(filename);
  if (!fp)
    return FDT_IMAGE_TYPE_UNKNOWN;

  char sig[FDT_IMAGE_HEADER_SIGNATURE_MAX];
  size_t n_read = fread(sig, sizeof(char), FDT_IMAGE_HEADER_SIGNATURE_MAX, fp);
  fdt_img_file_close(fp);

  // Identify image file type by the header signature

  if (n_read != FDT_IMAGE_HEADER_SIGNATURE_MAX) {
    return FDT_IMAGE_TYPE_UNKNOWN;
  }

  if (fdt_strncmp(sig, HFE_IMAGE_HEADER_SIGNATURE, fdt_strlen(HFE_IMAGE_HEADER_SIGNATURE)) == 0) {
    return FDT_IMAGE_TYPE_HFE;
  }

  return FDT_IMAGE_TYPE_UNKNOWN;
}
