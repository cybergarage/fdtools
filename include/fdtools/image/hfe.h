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

#ifndef _FDTOOLS_IMG_HFE_H_
#define _FDTOOLS_IMG_HFE_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HFE_FILE_HEADER_SIGNATURE "HXCPICFE"

#define HFE_IBMPC_DD_FLOPPYMODE 0x00
#define HFE_IBMPC_HD_FLOPPYMODE 0x01
#define HFE_ATARIST_DD_FLOPPYMODE 0x02
#define HFE_ATARIST_HD_FLOPPYMODE 0x03
#define HFE_AMIGA_DD_FLOPPYMODE 0x04
#define HFE_AMIGA_HD_FLOPPYMODE 0x05
#define HFE_CPC_DD_FLOPPYMODE 0x06
#define HFE_GENERIC_SHUGGART_DD_FLOPPYMODE 0x07
#define HFE_IBMPC_ED_FLOPPYMODE 0x08
#define HFE_MSX2_DD_FLOPPYMODE 0x09
#define HFE_C64_DD_FLOPPYMODE 0x0A
#define HFE_EMU_SHUGART_FLOPPYMODE 0x0B
#define HFE_S950_DD_FLOPPYMODE 0x0C
#define HFE_S950_HD_FLOPPYMODE 0x0D
#define HFE_DISABLE_FLOPPYMODE 0xFE

#define HFE_ISOIBM_MFM_ENCODING 0x00
#define HFE_AMIGA_MFM_ENCODING 0x01
#define HFE_ISOIBM_FM_ENCODING 0x02
#define HFE_EMU_FM_ENCODING 0x03
#define HFE_UNKNOWN_ENCODING 0xFF

typedef struct HFE_FILE_FORMAT_HEADER_ {
  unsigned char HEADERSIGNATURE[8];
  unsigned char formatrevision;
  unsigned char number_of_track;
  unsigned char number_of_side;
  unsigned char track_encoding;
  unsigned short bitRate;
  unsigned short floppyRPM;
  unsigned char floppyinterfacemode;
  unsigned char dnu;
  unsigned short track_list_offset;
  unsigned char write_allowed;
  unsigned char single_step;
  unsigned char track0s0_altencoding;
  unsigned char track0s0_encoding;
  unsigned char track0s1_altencoding;
  unsigned char track0s1_encoding;
} HFE_FILE_FORMAT_HEADER;

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_HFE_H_ */
