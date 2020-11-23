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

#include <fdtools/img/sector.h>

FdtImageSector* fdt_image_sector_new()
{
  FdtImageSector* sector = (FdtImageSector*)malloc(sizeof(FdtImageSector));
  if (!sector) {
    return NULL;
  }

  fdt_list_node_init((FdtList*)sector);

  fdt_image_sector_setcylindernumber(sector, 0);
  fdt_image_sector_setsidenumber(sector, 0);
  fdt_image_sector_setnumber(sector, 0);
  fdt_image_sector_setsize(sector, 0);
  fdt_image_sector_setdata(sector, NULL);

  return sector;
}

void fdt_image_sector_delete(FdtImageSector* sector)
{
  fdt_list_remove((FdtList*)sector);
  free(sector);
}