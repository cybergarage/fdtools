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
  int cylinder_number;
  int side_number;
  int number;
  size_t size;
  byte* data;
} FdtImageSector, FdtImageSectors;

FdtImageSectors* fdt_image_sectors_new();
void fdt_image_sectors_delete(FdtImageSectors* sectors);
size_t fdt_image_sectors_getnumberofcylinder(FdtImageSectors* sectors);
void fdt_image_sectors_print(FdtImageSectors* sectors);

#define fdt_image_sectors_size(sectors) fdt_list_size((FdtList*)sectors)
#define fdt_image_sectors_gets(sectors) (FdtImageSector*)fdt_list_gets((FdtList*)sectors)
#define fdt_image_sectors_clear(sectors) fdt_list_clear((FdtList*)sectors, (FDT_LIST_DESTRUCTORFUNC)fdt_image_sector_delete)

FdtImageSector* fdt_image_sector_new();
void fdt_image_sector_delete(FdtImageSector* sector);

#define fdt_image_sector_next(sector) (FdtImageSector*)fdt_list_next((FdtList*)sector)

#define fdt_image_sector_setcylindernumber(sector, n) (sector->cylinder_number = n)
#define fdt_image_sector_setsidenumber(sector, n) (sector->side_number = n)
#define fdt_image_sector_setnumber(sector, n) (sector->number = n)
#define fdt_image_sector_setsize(sector, n) (sector->size = n)
#define fdt_image_sector_setdata(sector, v) (sector->data = v)

#define fdt_image_sector_getcylindernumber(sector) (sector->cylinder_number)
#define fdt_image_sector_getsidenumber(sector) (sector->side_number)
#define fdt_image_sector_getnumber(sector) (sector->number)
#define fdt_image_sector_getsize(sector) (sector->size)
#define fdt_image_sector_getdata(sector) (sector->data)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_SECTOR_H_ */
