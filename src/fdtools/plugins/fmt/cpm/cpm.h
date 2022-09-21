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

#ifndef _FDTOOLS_CPM_FORMAT_H_
#define _FDTOOLS_CPM_FORMAT_H_

#include <fdtools/fmt/format.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FDT_CPM_START_TRACK_NO 2
#define FDT_CPM_END_TRACK_NO 3

#define E5H 0xE5

typedef struct FDT_ATTR_PACKED {
  byte_t UserNumber;
  byte_t Filename[8];
  byte_t Type[3];
  byte_t EX;
  byte_t S2;
  byte_t S1;
  byte_t RC;
  byte_t AL[16];
} FdtCpmDirectory;

FdtFormat* fdt_cpm_format_new(void);

const char* fdt_cpm_format_gettypeid(FdtFormat*);
bool fdt_cpm_format_format(FdtFormat*, FdtError* err);
bool fdt_cpm_format_list(FdtFormat*, FdtFiles*, FdtError* err);
bool fdt_cpm_format_add(FdtFormat*, FdtFile*, FdtError* err);
bool fdt_cpm_format_del(FdtFormat*, FdtFile*, FdtError* err);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_CPM_FORMAT_H_ */
