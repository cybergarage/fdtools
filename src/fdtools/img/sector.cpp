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

#include <fdtools/img/error.h>
#include <fdtools/img/sector.h>

FdtImageSector* fdt_image_sector_new()
{
  FdtImageSector* sector = (FdtImageSector*)calloc(sizeof(FdtImageSector), 1);
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

  if (fdt_image_sector_getcylindernumber(sector) < 0)
    return false;
  if (fdt_image_sector_getheadnumber(sector) < 0)
    return false;
  if (fdt_image_sector_getnumber(sector) < 1)
    return false;

  return true;
}

bool fdt_image_sector_setdata(FdtImageSector* sector, byte_t* data)
{
  if (!sector)
    return false;

  if (sector->data) {
    free(sector->data);
  }

  sector->data = data;

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

FdtImageSector* fdt_image_sector_copy(FdtImageSector* sector)
{
  FdtImageSector* other = fdt_image_sector_new();
  if (!other)
    return NULL;

  fdt_image_sector_setcylindernumber(other, fdt_image_sector_getcylindernumber(sector));
  fdt_image_sector_setheadnumber(other, fdt_image_sector_getheadnumber(sector));
  fdt_image_sector_setnumber(other, fdt_image_sector_getnumber(sector));
  fdt_image_sector_setsize(other, fdt_image_sector_getsize(sector));

  if (sector->data) {
    byte_t* data = (byte_t*)malloc(sector->size);
    if (!data) {
      fdt_image_sector_delete(other);
      return NULL;
    }
    memcpy(data, sector->data, sector->size);
    fdt_image_sector_setdata(other, data);
  }

  return other;
}

bool fdt_image_sector_equals(FdtImageSector* sector, FdtImageSector* other, FdtError* err)
{
  if (!sector || !other)
    return false;

  if ((sector->cylinder_number != other->cylinder_number) || (sector->head_number != other->head_number) || (sector->number != other->number) || (sector->size != other->size) || (!sector->data) || (!other->data) || (memcmp(sector->data, other->data, sector->size) != 0)) {
    fdt_error_setmessage(err, FDT_IMAGE_SECTOR_SIZE_PRINTF_FORMAT " != " FDT_IMAGE_SECTOR_SIZE_PRINTF_FORMAT, sector->cylinder_number, sector->head_number, sector->number, sector->size, other->cylinder_number, other->head_number, other->number, other->size);
    return false;
  }

  return true;
}
