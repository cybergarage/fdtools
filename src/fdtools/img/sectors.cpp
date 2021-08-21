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

#include <fdtools/img/error.h>
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

FdtImageSector* fdt_image_sectors_getsector(FdtImageSectors* sectors, FdtTrackNumber c, FdtHeadNumber h, FdtSectorNumber n)
{
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    if (fdt_image_sector_gettracknumber(sector) != c)
      continue;
    if (fdt_image_sector_getheadnumber(sector) != h)
      continue;
    if (fdt_image_sector_getnumber(sector) != n)
      continue;
    return sector;
  }
  return NULL;
}

size_t fdt_image_sectors_getnumberoftrack(FdtImageSectors* sectors)
{
  size_t max_track_idx = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    size_t track_idx = fdt_image_sector_gettracknumber(sector);
    if (track_idx < max_track_idx)
      continue;
    max_track_idx = track_idx;
  }
  return (max_track_idx + 1);
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

size_t fdt_image_sectors_getnumberofsector(FdtImageSectors* sectors)
{
  size_t max_sector_no = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    size_t sector_no = fdt_image_sector_getnumber(sector);
    if (sector_no < max_sector_no)
      continue;
    max_sector_no = sector_no;
  }
  return max_sector_no;
}

size_t fdt_image_sectors_getnumberoftracksector(FdtImageSectors* sectors, FdtTrackNumber c, FdtHeadNumber h)
{
  size_t max_sector_no = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    if (fdt_image_sector_gettracknumber(sector) != c)
      continue;
    if (fdt_image_sector_getheadnumber(sector) != h)
      continue;
    size_t sector_no = fdt_image_sector_getnumber(sector);
    if (sector_no < max_sector_no)
      continue;
    max_sector_no = sector_no;
  }
  return max_sector_no;
}

size_t fdt_image_sectors_getmaxsectorsize(FdtImageSectors* sectors)
{
  size_t max_sector_size = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    size_t sector_size = fdt_image_sector_getsize(sector);
    if (sector_size < max_sector_size)
      continue;
    max_sector_size = sector_size;
  }
  return max_sector_size;
}

size_t fdt_image_sectors_gettotaldatasize(FdtImageSectors* sectors)
{
  size_t total_sector_size = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    total_sector_size += fdt_image_sector_getsize(sector);
  }
  return total_sector_size;
}

size_t fdt_image_sectors_gettracksize(FdtImageSectors* sectors, FdtTrackNumber c, FdtHeadNumber h)
{
  size_t track_total_sector_size = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    if (fdt_image_sector_gettracknumber(sector) != c)
      continue;
    if (fdt_image_sector_getheadnumber(sector) != h)
      continue;
    track_total_sector_size += fdt_image_sector_getsize(sector);
  }
  return track_total_sector_size;
}

byte_t* fdt_image_sectors_gettrackbytes(FdtImageSectors* sectors, FdtTrackNumber c, FdtHeadNumber h)
{
  size_t track_size = fdt_image_sectors_gettracksize(sectors, c, h);
  byte_t* track_data = (byte_t*)calloc(track_size, sizeof(byte_t));
  if (!track_data)
    return NULL;

  size_t track_offset = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    if (fdt_image_sector_gettracknumber(sector) != c)
      continue;
    if (fdt_image_sector_getheadnumber(sector) != h)
      continue;
    size_t sector_size = fdt_image_sector_getsize(sector);
    byte_t* sector_bytes = fdt_image_sector_getdata(sector);
    if (sector_size == 0 || !sector_bytes)
      continue;
    memcpy(track_data + track_offset, sector_bytes, sector_size);
    track_offset += sector_size;
  }

  return track_data;
}

FdtImageSector* fdt_image_sectors_geterrorsector(FdtImageSectors* sectors)
{
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    if (fdt_image_sector_hasdata(sector))
      continue;
    return sector;
  }
  return NULL;
}

int fdt_image_sectors_getnerrorsectors(FdtImageSectors* sectors)
{
  int error_cnt = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    if (fdt_image_sector_hasdata(sector))
      continue;
    fdt_image_sector_incrementerrorcount(sector);
  }
  return error_cnt;
}

FdtImageSectors* fdt_image_sectors_copy(FdtImageSectors* sectors, FdtError* err)
{
  FdtImageSectors* others = fdt_image_sectors_new();
  if (!others)
    return NULL;

  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    FdtImageSector* other = fdt_image_sector_copy(sector);
    if (!other) {
      fdt_image_sectors_delete(others);
      return NULL;
    }
    fdt_image_sectors_addsector(others, other);
  }

  return others;
}

bool fdt_image_sectors_issorted(FdtImageSectors* sectors)
{
  return fdt_list_issorted((FdtList*)sectors, (FDT_LIST_COMPAREFUNC)fdt_image_sector_compare);
}

bool fdt_image_sectors_sort(FdtImageSectors* sectors)
{
  return fdt_list_sort((FdtList*)sectors, (FDT_LIST_COMPAREFUNC)fdt_image_sector_compare);
}

bool fdt_image_sectors_equals(FdtImageSectors* sectors, FdtImageSectors* others, FdtError* err)
{
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    size_t c = fdt_image_sector_gettracknumber(sector);
    size_t h = fdt_image_sector_getheadnumber(sector);
    size_t s = fdt_image_sector_getnumber(sector);
    FdtImageSector* other = fdt_image_sectors_getsector(others, c, h, s);
    if (!other) {
      fdt_error_setmessage(err, "Not found " FDT_IMAGE_MESSAGE_SECTOR_PRINTF_FORMAT, c, h, s);
      return false;
    }
    if (!fdt_image_sector_equals(sector, other, err))
      return false;
  }
  return true;
}

void fdt_image_sectors_print(FdtImageSectors* sectors)
{
  int n = 0;
  for (FdtImageSector* sector = fdt_image_sectors_gets(sectors); sector; sector = fdt_image_sector_next(sector)) {
    printf("[%04d] " FDT_IMAGE_MESSAGE_SECTOR_SIZE_PRINTF_FORMAT "\n",
        n,
        fdt_image_sector_gettracknumber(sector),
        fdt_image_sector_getheadnumber(sector),
        fdt_image_sector_getnumber(sector),
        fdt_image_sector_getsize(sector));
    n++;
  }
}
