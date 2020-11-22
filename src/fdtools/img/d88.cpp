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

FdtD88Image* fdt_d88_image_new(void)
{
  FdtD88Image* header = (FdtD88Image*)malloc(sizeof(FdtD88Image));
  if (!header) {
    return NULL;
  }
  fdt_image_init((FdtImage*)header);
  return header;
}

void fdt_d88_image_delete(FdtD88Image* header)
{
  free(header);
}

bool fdt_d88_image_load(FdtD88Image* header, FILE* fp)
{
  byte header_buf[sizeof(FdtD88Header)];
  if (!fdt_file_read(fp, header_buf, sizeof(header_buf)))
    return false;

  FdtD88Header raw_header;
  if (!fdt_d88_raw_header_parse(&raw_header, header_buf))
    return false;

  for (int n = 0; n < D88_HEADER_NUMBER_OF_SECTOR; n++) {
    size_t offset = raw_header.track_offset[n];
    if (offset == 0) {
      continue;
    }
    FdtD88RawSector raw_sector;
    if (!fdt_d88_raw_sector_load(&raw_sector, fp, n, offset))
      return false;
  }

  return true;
}

bool fdt_d88_raw_header_parse(FdtD88Header* header, byte* header_buf)
{
  memcpy(header, header_buf, sizeof(FdtD88Header));
  fdt_d88_raw_header_print(header);
  return true;
}

void fdt_d88_raw_header_print(FdtD88Header* header)
{
  printf("name:          %s\n", header->name);
  printf("reserve:       %02X%02X%02X%02X%02X%02X%02X%02X%02X\n", header->reserve[0], header->reserve[1], header->reserve[2], header->reserve[3], header->reserve[4], header->reserve[5], header->reserve[6], header->reserve[7], header->reserve[8]);
  printf("write_protect: %02X\n", header->write_protect);
  printf("disk_type:     %02X\n", header->disk_type);
  printf("disk_size:     %d\n", header->disk_size);
}

bool fdt_d88_raw_sector_load(FdtD88RawSector* sector, FILE* fp, int n, size_t offset)
{
  if (fseek(fp, offset, SEEK_SET) != 0)
    return false;

  byte sector_buf[sizeof(FdtD88RawSector)];
  if (!fdt_file_read(fp, sector_buf, sizeof(sector_buf)))
    return false;

  if (!fdt_d88_raw_sector_parse(sector, n, offset, sector_buf))
    return false;

  return true;
}

bool fdt_d88_raw_sector_parse(FdtD88RawSector* sector, int n, size_t offset, byte* sector_buf)
{
  memcpy(sector, sector_buf, sizeof(FdtD88RawSector));
  fdt_d88_raw_sector_print(sector, n, offset);
  return true;
}

void fdt_d88_raw_sector_print(FdtD88RawSector* sector, int n, size_t offset)
{
  printf("[%02d] %06X C:%02d H:%d R:%d N:%d SNUM:%d SSIZE:%d\n", n, offset, sector->c, sector->h, sector->r, sector->n, sector->number_of_sector, sector->size_of_data);
}
