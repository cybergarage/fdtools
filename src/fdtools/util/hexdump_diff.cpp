
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

#include <fdtools/util/hexdump.h>

bool fdt_hexdump_line_cmp(size_t offset, byte_t* buf_l, size_t line_l_len, byte_t* buf_r, size_t line_r_len)
{
  if (!buf_l || !buf_r)
    return false;
  if (line_l_len != line_r_len)
    return false;
  return memcmp(buf_l + offset, buf_r + offset, line_l_len) == 0 ? true : false;
}

void fdt_hexdump_compare_print(byte_t* buf_l, size_t buf_l_len, byte_t* buf_r, size_t buf_r_len)
{
  size_t offset = 0;
  while (offset < buf_l_len || offset < buf_r_len) {
    // Left image
    size_t line_l_len = FDT_HEXDUMP_LINE_BYTES;
    if (buf_l_len < (offset + line_l_len)) {
      line_l_len = buf_l_len % FDT_HEXDUMP_LINE_BYTES;
    }
    fdt_hexdump_line_print(buf_l, offset, line_l_len);

    // Left image
    size_t line_r_len = FDT_HEXDUMP_LINE_BYTES;
    if (buf_r_len < (offset + line_r_len)) {
      line_r_len = buf_r_len % FDT_HEXDUMP_LINE_BYTES;
    }

    if (fdt_hexdump_line_cmp(offset, buf_l, line_l_len, buf_r, line_r_len)) {
      printf("   ");
    }
    else {
      printf(" | ");
    }

    fdt_hexdump_line_print(buf_r, offset, line_r_len);

    printf("\n");

    offset += FDT_HEXDUMP_LINE_BYTES;
  }
}
