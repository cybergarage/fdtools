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

#ifndef _FDTOOLS_DOS_BPBT_H_
#define _FDTOOLS_DOS_BPBT_H_

#include <fdtools/fmt/format.h>
#include <fdtools/img/sector.h>

#ifdef __cplusplus
extern "C" {
#endif

// Microsoft FAT Specification - Microsoft Corporation August 30 2005
// 3.1 BPB structure common to FAT12, FAT16, and FAT32 implementations
// The BPB (BIOS Parameter Block) is located in the first sector of the volume in the Reserved Region.
// This sector is sometimes called the “boot sector” or the “0th sector”.
typedef struct FDT_ATTR_PACKED {
  // Jump instruction to boot code.
  byte_t BS_jmpBoot[3];
  // OEM Name Identifier. Can be set by a FAT implementation to any desired value.
  byte_t BS_OEMName[8];
  // Count of bytes per sector. This value may take on only the following values: 512, 1024, 2048 or 4096.
  byte_t BPB_BytsPerSec[2];
  // Number of sectors per allocation unit. This value must be a power of 2 that is greater than 0. The legal values are 1, 2, 4, 8, 16, 32, 64, and 128.
  byte_t BPB_SecPerClus[1];
  // Number of reserved sectors in the reserved region of the volume starting at the first sector of the volume.
  byte_t BPB_RsvdSecCnt[2];
  // The count of file allocation tables (FATs) on the volume.
  byte_t BPB_NumFATs[1];
  // For FAT12 and FAT16 volumes, this field contains the count of 32-byte directory entries in the root directory.
  byte_t BPB_RootEntCnt[2];
  // This field is the old 16-bit total count of sectors on the volume.
  byte_t BPB_TotSec16[2];
  // The legal values for this field are 0xF0, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, and 0xFF.
  byte_t BPB_Media[1];
  // This field is the FAT12/FAT16 16-bit count of sectors occupied by one FAT.
  byte_t BPB_FATSz16[2];
  // This field is only relevant for media that have a geometry.
  byte_t BPB_SecPerTrk[2];
  // This field contains the one based “count of heads”.
  byte_t BPB_NumHeads[2];
  // Count of hidden sectors preceding the partition that contains this FAT volume.
  byte_t BPB_HiddSec[4];
  // This field is the new 32-bit total count of sectors on the volume.
  byte_t BPB_TotSec32[4];
} FdtFatBpb;

FdtFatBpb* fdt_fat_bpb_new(void);
bool fdt_fat_bpb_delete(FdtFatBpb*);
bool fdt_fat_bpb_loadimagesector(FdtFatBpb*, FdtImageSector*, FdtError*);

#define fdt_fat_bpb_getjumpboot(bpb) ((bpb)->BS_jmpBoot)
#define fdt_fat_bpb_getoemname(bpb) ((bpb)->BS_OEMName)
#define fdt_fat_bpb_getbytespersec(bpb) ((bpb)->BPB_BytsPerSec)
#define fdt_fat_bpb_getsecperclus(bpb) ((bpb)->BPB_SecPerClus[0])
#define fdt_fat_bpb_getrsvdseccnt(bpb) ((bpb)->BPB_RsvdSecCnt)
#define fdt_fat_bpb_getnumfats(bpb) ((bpb)->BPB_NumFATs[0])
#define fdt_fat_bpb_getrootentcnt(bpb) ((bpb)->BPB_RootEntCnt)
#define fdt_fat_bpb_gettotsec16(bpb) ((bpb)->BPB_TotSec16)
#define fdt_fat_bpb_getmedia(bpb) ((bpb)->BPB_Media[0])
#define fdt_fat_bpb_getfatsz16(bpb) ((bpb)->BPB_FATSz16)
#define fdt_fat_bpb_getsecpertrk(bpb) ((bpb)->BPB_SecPerTrk)
#define fdt_fat_bpb_getnumheads(bpb) ((bpb)->BPB_NumHeads)
#define fdt_fat_bpb_gethiddsec(bpb) ((bpb)->BPB_HiddSec)
#define fdt_fat_bpb_gettotsec32(bpb) ((bpb)->BPB_TotSec32)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_DOS_BPBT_H_ */
