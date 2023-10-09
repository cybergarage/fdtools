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

// Microsoft FAT Specification - Microsoft Corporation August 30 2005
// 3.2 Extended BPB structure for FAT12 and FAT16 volumes
// If the volume has been formatted FAT12 or FAT16, the remainder of the BPB structure must be as described below:
typedef struct FDT_ATTR_PACKED {
  // Set value to 0x80 or 0x00.
  byte_t BS_DrvNum[1];
  // Reserved. Set value to 0x00.
  byte_t BS_Reserved1[1];
  // Extended boot signature. Set value to 0x29 if either of the following two fields are non-zero.
  byte_t BS_BootSig[1];
  // Volume serial number.
  byte_t BS_VolID[4];
  // Volume label. This field matches the 11-byte volume label recorded in the root directory.
  byte_t BS_VolLab[11];
  // One of the strings “FAT12 ”, “FAT16 ”, or “FAT ”. NOTE: This string is informational only and does not determine the FAT type.
  byte_t BS_FilSysType[8];
  // Set to 0x00.
  byte_t Blank[448];
  // Set to 0x55 (at byte offset 510) and 0xAA (at byte offset 511).
  byte_t Signature_word[2];
  // All remaining bytes in sector.
  // Set to 0x00 (only for media where BPB_BytsPerSec > 512.
} FdtFatBpbExtended;

FdtFatBpb* fdt_fat_bpb_new(void);
bool fdt_fat_bpb_delete(FdtFatBpb*);
bool fdt_fat_bpb_readimagesector(FdtFatBpb*, FdtImageSector*, FdtError*);

FdtFatBpbExtended* fdt_fat_bpbex_new(void);
bool fdt_fat_bpbex_delete(FdtFatBpbExtended*);
bool fdt_fat_bpbex_readimagesector(FdtFatBpbExtended*, FdtImageSector*, FdtError*);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_DOS_FORMAT_H_ */
