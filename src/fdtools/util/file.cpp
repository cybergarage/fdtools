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

const char* fdt_file_mode2str(FdtFileMode mode)
{
  switch (mode) {
  case FDT_FILE_READ:
    return "rb";
    break;
  case FDT_FILE_WRITE:
    return "wb";
    break;
  }
  return NULL;
}

FILE* fdt_file_open(const char* filename, FdtFileMode mode)
{
  const char* fmode = fdt_file_mode2str(mode);
  if (!fmode)
    return NULL;
  return fopen(filename, fmode);
}

bool fdt_file_close(FILE* fp)
{
  return (fclose(fp) == 0) ? true : false;
}

FILE* fdt_file_memopen(byte_t* buf, size_t n, FdtFileMode mode)
{
  const char* fmode = fdt_file_mode2str(mode);
  if (!fmode)
    return NULL;
  return fmemopen(buf, n, fmode);
}

bool fdt_file_memclose(FILE* fp)
{
  return (fclose(fp) == 0) ? true : false;
}

bool fdt_file_read(FILE* fp, void* buf, size_t n)
{
  return (fread(buf, 1, n, fp) == n) ? true : false;
}

bool fdt_file_write(FILE* fp, void* buf, size_t n)
{
  return (fwrite(buf, 1, n, fp) == n) ? true : false;
}

bool fdt_file_seek(FILE* fp, long offset, int whence)
{
  return (fseek(fp, offset, whence) == 0) ? true : false;
}

bool fdt_file_hasprefix(const char* filename, const char* prefix)
{
  return fdt_strncmp(filename, prefix, fdt_strlen(prefix)) == 0 ? true : false;
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
