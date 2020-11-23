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

#include <fdtools/img/sector.h>

FdtImageSectors* fdt_image_sectors_new()
{
  FdtImageSectors* sectors = (FdtImageSectors*)malloc(sizeof(FdtImageSectors));
  if (!sectors) {
    return NULL;
  }

  fdt_list_header_init((FdtList*)sectors);

  return sectors;
}

void fdt_image_sectors_delete(FdtImageSectors* sectors)
{
  fdt_image_sectors_clear(sectors);
  free(sectors);
}

size_t fdt_image_sectors_getnumberofcylinder(FdtImageSectors* sectors)
{
  size_t max_cylinder_idx = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    size_t cylinder_idx = fdt_image_sector_getcylindernumber(sector);
    if (cylinder_idx < max_cylinder_idx)
      continue;
    max_cylinder_idx = cylinder_idx;
  }
  return (max_cylinder_idx + 1);
}

size_t fdt_image_sectors_getnumberofhead(FdtImageSectors* sectors)
{
  size_t max_head_idx = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    size_t head_idx = fdt_image_sector_getheadnumber(sector);
    if (head_idx < max_head_idx)
      continue;
    max_head_idx = head_idx;
  }
  return (max_head_idx + 1);
}

void fdt_image_sectors_print(FdtImageSectors* sectors)
{
  int n = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    printf("[%02d] C:%02d H:%d R:%d SIZE:%ld\n",
        n,
        fdt_image_sector_getcylindernumber(sector),
        fdt_image_sector_getheadnumber(sector),
        fdt_image_sector_getnumber(sector),
        fdt_image_sector_getsize(sector));
    n++;
  }
}
