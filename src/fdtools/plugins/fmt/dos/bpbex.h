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

#ifndef _FDTOOLS_DOS_BPBTEX_H_
#define _FDTOOLS_DOS_BPBTEX_H_

#include <fdtools/fmt/format.h>
#include <fdtools/img/sector.h>

#ifdef __cplusplus
extern "C" {
#endif

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

FdtFatBpbExtended* fdt_fat_bpbex_new(void);
bool fdt_fat_bpbex_delete(FdtFatBpbExtended*);
bool fdt_fat_bpbex_loadimagesector(FdtFatBpbExtended*, FdtImageSector*, FdtError*);

#define fdt_fat_bpbex_getdrivenum(bpbex) ((bpbex)->BS_DrvNum[0])
#define fdt_fat_bpbex_getreserved1(bpbex) ((bpbex)->BS_Reserved1[0])
#define fdt_fat_bpbex_getbootsig(bpbex) ((bpbex)->BS_BootSig[0])
#define fdt_fat_bpbex_getvolid(bpbex) ((bpbex)->BS_VolID)
#define fdt_fat_bpbex_getvollab(bpbex) ((bpbex)->BS_VolLab)
#define fdt_fat_bpbex_getfilstype(bpbex) ((bpbex)->BS_FilSysType)
#define fdt_fat_bpbex_getblank(bpbex) ((bpbex)->Blank)
#define fdt_fat_bpbex_getsignatureword(bpbex) ((bpbex)->Signature_word)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_DOS_BPBTEX_H_ */
