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
#include <string.h>

#include <fdtools/plugins/d88/d88.h>

FdtImage* fdt_d88_image_new(void)
{
  FdtImage* img = fdt_image_file_new();
  if (!img)
    return NULL;

  fdt_image_setgettypeid(img, fdt_d88_image_gettypeid);
  fdt_image_sethasext(img, fdt_d88_image_hasext);
  fdt_image_setloader(img, fdt_d88_image_load);
  fdt_image_setexporter(img, fdt_d88_image_export);

  return img;
}

const char* fdt_d88_image_gettypeid(FdtImage* img)
{
  return "D88";
}

bool fdt_d88_image_hasext(FdtFileImage* img, const char* filename)
{
  if (fdt_file_hasextension(filename, D88_EXTENTION_D88))
    return true;
  if (fdt_file_hasextension(filename, D88_EXTENTION_88D))
    return true;
  if (fdt_file_hasextension(filename, D88_EXTENTION_D77))
    return true;
  if (fdt_file_hasextension(filename, D88_EXTENTION_D68))
    return true;
  if (fdt_file_hasextension(filename, D88_EXTENTION_D98))
    return true;
  if (fdt_file_hasextension(filename, D88_EXTENTION_D8U))
    return true;
  if (fdt_file_hasextension(filename, D88_EXTENTION_1DD))
    return true;
  return false;
}

void fdt_d88_header_setconfigerror(FdtD88Header* d88_header, FdtImage* img, FdtError* err)
{
  FdtImageDensity density = fdt_image_getsupposeddensity(img);
  fdt_error_setmessage(err, FDT_D88_MESSAGE_HEADER FDT_IMAGE_MESSAGE_UNKNOWN_DENSITY_FORMAT " (%ld:%ld:%ld:%ld)", fdt_image_density_getstring(density), fdt_image_getnumberofcylinder(img), fdt_image_getnumberofhead(img), fdt_image_getnumberofsector(img), fdt_image_getsectorsize(img));
}

bool fdt_d88_header_setconfig(FdtD88Header* d88_header, FdtImage* img, FdtError* err)
{
  memset(d88_header, 0, sizeof(FdtD88Header));

  if (fdt_image_hasname(img)) {
    fdt_strncpy(d88_header->name, fdt_image_getname(img), D88_NAME_MAXLEN);
  }
  d88_header->write_protect = fdt_image_iswriteprotectenabled(img) ? D88_WRITE_PROTECT_ENABLED : D88_WRITE_PROTECT_NONE;
  d88_header->disk_size = (uint32_t)fdt_image_getsize(img);

  // Sets a disk type

  FdtImageDensity density = fdt_image_getsupposeddensity(img);
  switch (density) {
  case FDT_IMAGE_DENSITY_SD:
    switch (fdt_image_getnumberofhead(img)) {
    case 1:
      d88_header->disk_type = D88_DISK_TYPE_1D;
      break;
    case 2:
      d88_header->disk_type = D88_DISK_TYPE_2D;
      break;
    default:
      fdt_d88_header_setconfigerror(d88_header, img, err);
      return false;
    }
    break;
  case FDT_IMAGE_DENSITY_DD:
    switch (fdt_image_getnumberofhead(img)) {
    case 1:
      d88_header->disk_type = D88_DISK_TYPE_1DD;
      break;
    case 2:
      d88_header->disk_type = D88_DISK_TYPE_2DD;
      break;
    default:
      fdt_d88_header_setconfigerror(d88_header, img, err);
      return false;
    }
    break;
  case FDT_IMAGE_DENSITY_HD:
    switch (fdt_image_getnumberofhead(img)) {
    case 2:
      d88_header->disk_type = D88_DISK_TYPE_2HD;
      break;
    default:
      fdt_d88_header_setconfigerror(d88_header, img, err);
      return false;
    }
    break;
  default:
    fdt_d88_header_setconfigerror(d88_header, img, err);
    return false;
  }

  // Sets track offsets

  uint32_t track_offset = sizeof(FdtD88Header);
  for (int c = 0; c < (D88_HEADER_NUMBER_OF_SECTOR / D88_HEADER_NUMBER_OF_HEADER); c++) {
    for (int h = 0; h < D88_HEADER_NUMBER_OF_HEADER; h++) {
      int n = (D88_HEADER_NUMBER_OF_HEADER * c) + h;
      d88_header->track_offset[n] = track_offset;
      size_t track_total_size = fdt_image_gettracksize(img, c, h);
      if (track_total_size <= 0) {
        d88_header->track_offset[n] = 0;
        break;
      }
      track_offset += sizeof(FdtD88SectorHeader);
      track_offset += track_total_size;
    }
  }

  return true;
}

void fdt_d88_sector_header_setconfigerror(FdtD88SectorHeader* d88_sector_header, FdtImageSector* sector, FdtImageDensity density, size_t number_of_sector, FdtError* err)
{
  fdt_error_setmessage(err, FDT_D88_MESSAGE_HEADER FDT_IMAGE_MESSAGE_UNKNOWN_DENSITY_FORMAT " %ld", fdt_image_density_getstring(density), number_of_sector);
}

bool fdt_d88_sector_header_setconfig(FdtD88SectorHeader* d88_sector_header, FdtImageSector* sector, FdtImageDensity density, size_t number_of_sector, FdtError* err)
{
  memset(d88_sector_header, 0, sizeof(FdtD88SectorHeader));

  size_t sector_size = fdt_image_sector_getsize(sector);

  d88_sector_header->c = fdt_image_sector_getcylindernumber(sector);
  d88_sector_header->h = fdt_image_sector_getheadnumber(sector);
  d88_sector_header->r = 1;
  d88_sector_header->number_of_sector = (uint16_t)number_of_sector;

  switch (density) {
  case FDT_IMAGE_DENSITY_SD:
    d88_sector_header->density = D88_SECTOR_DENSITY_SINGLE;
    break;
  case FDT_IMAGE_DENSITY_DD:
    d88_sector_header->density = D88_SECTOR_DENSITY_DOUBLE;
    break;
  case FDT_IMAGE_DENSITY_HD:
    d88_sector_header->density = D88_SECTOR_DENSITY_HIGH;
    break;
  default:
    fdt_d88_sector_header_setconfigerror(d88_sector_header, sector, density, number_of_sector, err);
    return false;
  }

  switch (sector_size) {
  case 128:
    d88_sector_header->n = D88_SECTOR_N_128;
    break;
  case 256:
    d88_sector_header->n = D88_SECTOR_N_256;
    break;
  case 512:
    d88_sector_header->n = D88_SECTOR_N_512;
    break;
  case 1024:
    d88_sector_header->n = D88_SECTOR_N_1024;
    break;
  default:
    fdt_d88_sector_header_setconfigerror(d88_sector_header, sector, density, number_of_sector, err);
    return false;
  }

  d88_sector_header->deleted_mark = D88_SECTOR_DELETED_MARK_NONE;
  d88_sector_header->status = D88_SECTOR_STATUS_NORMAL;
  d88_sector_header->size_of_data = sector_size;

  return true;
}
