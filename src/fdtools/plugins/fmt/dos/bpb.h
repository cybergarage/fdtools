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
#include <fdtools/util/bytes.h>

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
FdtFatBpb* fdt_fat_bpb_from(byte_t*);
bool fdt_fat_bpb_delete(FdtFatBpb*);
bool fdt_fat_bpb_loadimagesector(FdtFatBpb*, FdtImageSector*, FdtError*);

inline byte_t* fdt_fat_bpb_getjumpboot(FdtFatBpb* bpb) { return (bpb)->BS_jmpBoot; }
inline byte_t* fdt_fat_bpb_getoemname(FdtFatBpb* bpb) { return (bpb)->BS_OEMName; }
inline size_t fdt_fat_bpb_getbytespersec(FdtFatBpb* bpb) { return fdt_ushort_fromlebytes((bpb)->BPB_BytsPerSec); }
inline size_t fdt_fat_bpb_getsecperclus(FdtFatBpb* bpb) { return (bpb)->BPB_SecPerClus[0]; }
inline size_t fdt_fat_bpb_getrsvdseccnt(FdtFatBpb* bpb) { return fdt_ushort_fromlebytes((bpb)->BPB_RsvdSecCnt); }
inline size_t fdt_fat_bpb_getnumfats(FdtFatBpb* bpb) { return (bpb)->BPB_NumFATs[0]; }
inline size_t fdt_fat_bpb_getrootentcnt(FdtFatBpb* bpb) { return fdt_ushort_fromlebytes((bpb)->BPB_RootEntCnt); }
inline size_t fdt_fat_bpb_gettotsec16(FdtFatBpb* bpb) { return fdt_ushort_fromlebytes((bpb)->BPB_TotSec16); }
inline byte_t fdt_fat_bpb_getmedia(FdtFatBpb* bpb) { return (bpb)->BPB_Media[0]; }
inline byte_t* fdt_fat_bpb_getfatsz16(FdtFatBpb* bpb) { return (bpb)->BPB_FATSz16; }
inline size_t fdt_fat_bpb_getsecpertrk(FdtFatBpb* bpb) { return fdt_ushort_fromlebytes((bpb)->BPB_SecPerTrk); }
inline size_t fdt_fat_bpb_getnumheads(FdtFatBpb* bpb) { return fdt_ushort_fromlebytes((bpb)->BPB_NumHeads); }
inline byte_t* fdt_fat_bpb_gethiddsec(FdtFatBpb* bpb) { return (bpb)->BPB_HiddSec; }
inline byte_t* fdt_fat_bpb_gettotsec32(FdtFatBpb* bpb) { return (bpb)->BPB_TotSec32; }

inline void fdt_fat_bpb_setjumpboot(FdtFatBpb* bpb, const byte_t* v) { memcpy((bpb)->BS_jmpBoot, v, sizeof((bpb)->BS_jmpBoot)); }
inline void fdt_fat_bpb_setoemname(FdtFatBpb* bpb, const byte_t* v) { memcpy((bpb)->BS_OEMName, v, sizeof((bpb)->BS_OEMName)); }
inline void fdt_fat_bpb_setsecperclus(FdtFatBpb* bpb, size_t v) { (bpb)->BPB_SecPerClus[0] = v; }
inline void fdt_fat_bpb_setrsvdseccnt(FdtFatBpb* bpb, size_t v) { fdt_ushort_setlebytes(v, (bpb)->BPB_RsvdSecCnt); }
inline void fdt_fat_bpb_setnumfats(FdtFatBpb* bpb, size_t v) { (bpb)->BPB_NumFATs[0] = v; }
inline void fdt_fat_bpb_setrootentcnt(FdtFatBpb* bpb, size_t v) { fdt_ushort_setlebytes(v, (bpb)->BPB_RootEntCnt); }
inline void fdt_fat_bpb_settotsec16(FdtFatBpb* bpb, size_t v) { fdt_ushort_setlebytes(v, (bpb)->BPB_TotSec16); }
inline void fdt_fat_bpb_setmedia(FdtFatBpb* bpb, byte_t v) { (bpb)->BPB_Media[0] = v; }
inline void fdt_fat_bpb_setfatsz16(FdtFatBpb* bpb, size_t v) { fdt_ushort_setlebytes(v, (bpb)->BPB_FATSz16); }
inline void fdt_fat_bpb_setbytespersec(FdtFatBpb* bpb, size_t v) { fdt_ushort_setlebytes(v, (bpb)->BPB_BytsPerSec); }
inline void fdt_fat_bpb_setsecpertrk(FdtFatBpb* bpb, size_t v) { fdt_ushort_setlebytes(v, (bpb)->BPB_SecPerTrk); }
inline void fdt_fat_bpb_setnumheads(FdtFatBpb* bpb, size_t v) { fdt_ushort_setlebytes(v, (bpb)->BPB_NumHeads); }

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_DOS_BPBT_H_ */
