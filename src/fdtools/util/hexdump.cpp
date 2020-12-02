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

const size_t FDT_HEXDUMP_LINE_BYTES = 16;

void fdt_hexdump_print(byte* buf, size_t buf_len)
{
  for (size_t offset = 0; offset < buf_len; offset += FDT_HEXDUMP_LINE_BYTES) {
    size_t line_len = FDT_HEXDUMP_LINE_BYTES;
    if (buf_len < (offset + line_len)) {
      line_len = buf_len % FDT_HEXDUMP_LINE_BYTES;
    }
    printf("%04lX ", offset);
    for (size_t n = 0; n < (line_len / 2); n++) {
      printf("%02X", buf[offset + n] & 0xFF);
    }
    printf(" ");
    for (size_t n = (line_len / 2); n < line_len; n++) {
      printf("%02X", buf[offset + n] & 0xFF);
    }
    printf("\n");
  }
}
