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

#ifndef _FDTOOLS_IMG_SECTOR_H_
#define _FDTOOLS_IMG_SECTOR_H_

#include <fdtools/util/list.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  FDT_LIST_STRUCT_MEMBERS
} FdtImageSector, FdtImageSectors;

FdtImageSectors* fdt_image_sectors_new();
void fdt_image_sectors_delete(FdtImageSectors* sectors);

FdtImageSector* fdt_image_sector_new();
void fdt_image_sector_delete(FdtImageSector* sector);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_SECTOR_H_ */
