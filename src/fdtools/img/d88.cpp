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

FdtD88Header* fdt_d88_header_new(void)
{
  FdtD88Header* header = (FdtD88Header*)malloc(sizeof(FdtD88Header));
  if (!header) {
    return NULL;
  }
  fdt_image_header_init((FdtImageHeader*)header);
  return header;
}

void fdt_d88_header_delete(FdtD88Header* header)
{
  free(header);
}

bool fdt_d88_header_load(FdtD88Header* header, FILE* fp)
{
  byte header_buf[sizeof(FdtD88RawHeader)];
  if (!fdt_img_file_read(fp, header_buf, sizeof(header_buf)))
    return false;
  return fdt_d88_header_parse(header, header_buf);
}

bool fdt_d88_header_parse(FdtD88Header* header, byte* header_buf)
{
  FdtD88RawHeader* raw_header = (FdtD88RawHeader*)header_buf;
  fdt_d88_raw_header_print(raw_header);
  return true;
}

void fdt_d88_raw_header_print(FdtD88RawHeader* header)
{
  printf("name:          %s\n", header->name);
  printf("reserve:       %02X%02X%02X%02X%02X%02X%02X%02X%02X\n", header->reserve[0], header->reserve[1], header->reserve[2], header->reserve[3], header->reserve[4], header->reserve[5], header->reserve[6], header->reserve[7], header->reserve[8]);
  printf("write_protect: %02X\n", header->write_protect);
  printf("disk_type:     %02X\n", header->disk_type);
  printf("disk_size:     %d\n", header->disk_size);
}
