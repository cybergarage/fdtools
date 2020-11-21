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

#ifndef _FDTOOLS_IMG_D88_H_
#define _FDTOOLS_IMG_D88_H_

#include <fdtools/img/header.h>

#ifdef __cplusplus
extern "C" {
#endif

const char D88_EXTENTION_D88[] = "d88";
const char D88_EXTENTION_88D[] = "88d";
const char D88_EXTENTION_D77[] = "d77";
const char D88_EXTENTION_D68[] = "d68";
const char D88_EXTENTION_D98[] = "d98";
const char D88_EXTENTION_D8U[] = "d8u";
const char D88_EXTENTION_1DD[] = "1dd";

const int D88_HEADER_NUMBER_OF_TRACK = 82;
const int D88_HEADER_NUMBER_OF_HEADER = 2;
const int D88_HEADER_NUMBER_OF_SECTOR = D88_HEADER_NUMBER_OF_TRACK * D88_HEADER_NUMBER_OF_HEADER;
const int D88_HEADER_SIZE = (17 + 9 + 1 + 1 + 4 + (4 * D88_HEADER_NUMBER_OF_SECTOR));

const uint8_t D88_WRITE_PROTECT_NONE = 0x00;
const uint8_t D88_WRITE_PROTECT_ENABLED = 0x10;

const uint8_t D88_DISK_TYPE_2D = 0x00;
const uint8_t D88_DISK_TYPE_2DD = 0x10;
const uint8_t D88_DISK_TYPE_2HD = 0x20;
const uint8_t D88_DISK_TYPE_1D = 0x30;
const uint8_t D88_DISK_TYPE_1DD = 0x40;

typedef struct FDT_ATTR_PACKED {
  char name[17];
  uint8_t reserve[9];
  uint8_t write_protect;
  uint8_t disk_type;
  uint32_t disk_size;
  uint32_t track_offset[D88_HEADER_NUMBER_OF_SECTOR];
} FdtD88RawHeader;

typedef struct {
  FDT_IMAGE_CONFIG_MEMBERS
} FdtD88Header;

const uint8_t D88_TRACK_DELETED_MARK_NONE = 0x00;
const uint8_t D88_TRACK_DELETED_MARK_ENABLED = 0x10;

const uint8_t D88_TRACK_DENSITY_SINGLE = 0x40;
const uint8_t D88_TRACK_DENSITY_DOUBLE = 0x00;
const uint8_t D88_TRACK_DENSITY_HIGH = 0x01;

const uint8_t D88_TRACK_STATUS_NORMAL = 0x00;
const uint8_t D88_TRACK_STATUS_NORMA_DELETED = 0x10;
const uint8_t D88_TRACK_STATUS_CRC_ERROR = 0xA0;
const uint8_t D88_TRACK_STATUS_DATS_CRC_ERROR = 0xB0;
const uint8_t D88_TRACK_STATUS_NON_ADDRESS_MARK = 0xE0;
const uint8_t D88_TRACK_STATUS_NON_DATA_MARK = 0xF0;

typedef struct FDT_ATTR_PACKED {
  uint8_t c;
  uint8_t h;
  uint8_t r;
  uint8_t n;
  uint16_t number_of_sector;
  uint8_t density;
  uint8_t deleted_mark;
  uint8_t status;
  uint8_t reserve[5];
  uint16_t size_of_data;
} FdtD88RawSector;

FdtD88Header* fdt_d88_header_new(void);
void fdt_d88_header_delete(FdtD88Header*);
bool fdt_d88_header_load(FdtD88Header*, FILE*);

bool fdt_d88_raw_header_parse(FdtD88RawHeader*, byte*);
void fdt_d88_raw_header_print(FdtD88RawHeader*);
bool fdt_d88_raw_sector_load(FdtD88RawSector*, FILE* fp, int n, size_t offset);
bool fdt_d88_raw_sector_parse(FdtD88RawSector*, int, size_t, byte*);
void fdt_d88_raw_sector_print(FdtD88RawSector*, int n, size_t offset);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_D88_H_ */
