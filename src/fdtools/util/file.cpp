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

FILE* fdt_file_open(const char* filename, FdtFileMode mode)
{
  const char* fmode = NULL;
  switch (mode) {
  case FDT_FILE_READ:
    fmode = "rb";
    break;
  case FDT_FILE_WRITE:
    fmode = "rb";
    break;
  }

  if (!fmode)
    return NULL;

  return fopen(filename, fmode);
}

int fdt_file_close(FILE* fp)
{
  return fclose(fp);
}

bool fdt_file_read(FILE* fp, byte* buf, size_t n)
{
  return (fread(buf, 1, n, fp) == n) ? true : false;
}

bool fdt_file_hasextension(const char* filename, const char* extname)
{
  size_t filename_len = fdt_strlen(filename);
  size_t extname_len = fdt_strlen(extname);
  if (filename_len < extname_len)
    return false;
  size_t filename_ext_idx = filename_len - extname_len;
  return (fdt_strcmp((filename + filename_ext_idx), extname) == 0) ? true : false;
}
