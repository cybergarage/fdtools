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

#include <string.h>

#include <fdtools/img/sector.h>

FdtImageSector* fdt_image_sector_new()
{
  FdtImageSector* sector = (FdtImageSector*)malloc(sizeof(FdtImageSector));
  if (!sector) {
    return NULL;
  }

  fdt_list_node_init((FdtList*)sector);

  fdt_image_sector_setcylindernumber(sector, 0);
  fdt_image_sector_setheadnumber(sector, 0);
  fdt_image_sector_setnumber(sector, 0);
  fdt_image_sector_setsize(sector, 0);
  fdt_image_sector_setdata(sector, NULL);

  return sector;
}

bool fdt_image_sector_delete(FdtImageSector* sector)
{
  if (!sector)
    return false;

  fdt_list_remove((FdtList*)sector);
  if (sector->data) {
    free(sector->data);
  }
  free(sector);

  return true;
}

bool fdt_image_sector_isvalid(FdtImageSector* sector)
{
  if (!sector)
    return false;

  if (fdt_image_sector_getcylindernumber(sector) <= 0)
    return false;
  if (fdt_image_sector_getheadnumber(sector) <= 0)
    return false;
  if (fdt_image_sector_getnumber(sector) <= 0)
    return false;

  return true;
}

bool fdt_image_sector_hasdata(FdtImageSector* sector)
{
  if (!sector)
    return false;

  if (!sector->data || (sector->size == 0))
    return false;

  return true;
}

bool fdt_image_sector_equals(FdtImageSector* sector, FdtImageSector* other)
{
  if (!sector || !other)
    return false;

  if (sector->cylinder_number != other->cylinder_number)
    return false;
  if (sector->head_number != other->head_number)
    return false;
  if (sector->number != other->number)
    return false;
  if (sector->size != other->size)
    return false;

  return memcmp(sector->data, other->data, sector->size) == 0 ? true : false;
}
