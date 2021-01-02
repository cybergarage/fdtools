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

#include <fdtools/img/d88.h>
#include <fdtools/img/error.h>
#include <fdtools/util/file.h>
#include <fdtools/util/string.h>

bool fdt_d88_header_setconfig(FdtD88Header*, FdtFileImage*, FdtError* err);
bool fdt_d88_sector_header_setconfig(FdtD88SectorHeader*, FdtImageSector*, FdtDensity, size_t, FdtError* err);

bool fdt_d88_image_export(FdtFileImage* img, FdtError* err)
{
  if (!img)
    return false;

  FILE* fp = fdt_image_file_getfile(img);
  if (!fp)
    return false;

  FdtD88Header d88_header;
  if (!fdt_d88_header_setconfig(&d88_header, img, err))
    return false;

  if (!fdt_file_write(fp, &d88_header, sizeof(d88_header))) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  FdtDensity img_density = fdt_image_getdensity(img);
  for (int c = 0; c < (D88_HEADER_NUMBER_OF_SECTOR / D88_HEADER_NUMBER_OF_HEADER); c++) {
    for (int h = 0; h < D88_HEADER_NUMBER_OF_HEADER; h++) {
      size_t number_of_sector = fdt_image_getnumberoftracksector(img, c, h);
      if (number_of_sector <= 0)
        continue;
      for (int r = 1; r <= number_of_sector; r++) {
        FdtImageSector* sector = fdt_image_getsector(img, c, h, r);
        if (!sector)
          return false;
        if (r == 1) {
          FdtD88SectorHeader d88_sector_header;
          if (!fdt_d88_sector_header_setconfig(&d88_sector_header, sector, img_density, number_of_sector, err))
            return false;
          if (!fdt_file_write(fp, &d88_sector_header, sizeof(FdtD88SectorHeader))) {
            fdt_error_setlasterror(err, "");
            return false;
          }
        }
        size_t sector_size = fdt_image_sector_getsize(sector);
        if (!fdt_file_write(fp, fdt_image_sector_getdata(sector), sector_size)) {
          fdt_error_setlasterror(err, "");
          return false;
        }
      }
    }
  }

  return true;
}

bool fdt_d88_header_setconfig(FdtD88Header* d88_header, FdtFileImage* img, FdtError* err)
{
  memset(d88_header, 0, sizeof(FdtD88Header));

  if (fdt_image_hasname(img)) {
    fdt_strncpy(d88_header->name, fdt_image_getname(img), D88_NAME_MAXLEN);
  }
  d88_header->write_protect = fdt_image_getwriteprotect(img) ? D88_WRITE_PROTECT_ENABLED : D88_WRITE_PROTECT_NONE;
  d88_header->disk_size = (uint32_t)fdt_image_getsize(img);

  // Sets a disk type

  FdtDensity density = fdt_image_getdensity(img);
  switch (density) {
  case FDT_DENSITY_SD:
    switch (fdt_image_getnumberofhead(img)) {
    case 1:
      d88_header->disk_type = D88_DISK_TYPE_1D;
      break;
    case 2:
      d88_header->disk_type = D88_DISK_TYPE_2D;
      break;
    default:
      fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_UNKNOWN_DENSITY_FORMAT, fdt_image_density_getstring(density));
      return false;
    }
    break;
  case FDT_DENSITY_DD:
    switch (fdt_image_getnumberofhead(img)) {
    case 1:
      d88_header->disk_type = D88_DISK_TYPE_1DD;
      break;
    case 2:
      d88_header->disk_type = D88_DISK_TYPE_2DD;
      break;
    default:
      fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_UNKNOWN_DENSITY_FORMAT, fdt_image_density_getstring(density));
      return false;
    }
    break;
  case FDT_DENSITY_HD:
    switch (fdt_image_getnumberofhead(img)) {
    case 2:
      d88_header->disk_type = D88_DISK_TYPE_2HD;
      break;
    default:
      fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_UNKNOWN_DENSITY_FORMAT, fdt_image_density_getstring(density));
      return false;
    }
    break;
  default:
    fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_UNKNOWN_DENSITY_FORMAT, fdt_image_density_getstring(density));
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

bool fdt_d88_sector_header_setconfig(FdtD88SectorHeader* d88_sector_header, FdtImageSector* sector, FdtDensity density, size_t number_of_sector, FdtError* err)
{
  memset(d88_sector_header, 0, sizeof(FdtD88SectorHeader));

  size_t sector_size = fdt_image_sector_getsize(sector);

  d88_sector_header->c = fdt_image_sector_getcylindernumber(sector);
  d88_sector_header->h = fdt_image_sector_getheadnumber(sector);
  d88_sector_header->r = 1;
  d88_sector_header->number_of_sector = (uint16_t)number_of_sector;

  switch (density) {
  case FDT_DENSITY_SD:
    d88_sector_header->density = D88_SECTOR_DENSITY_SINGLE;
    break;
  case FDT_DENSITY_DD:
    d88_sector_header->density = D88_SECTOR_DENSITY_DOUBLE;
    break;
  case FDT_DENSITY_HD:
    d88_sector_header->density = D88_SECTOR_DENSITY_HIGH;
    break;
  default:
    fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_UNKNOWN_DENSITY_FORMAT, fdt_image_density_getstring(density));
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
    return false;
  }

  d88_sector_header->deleted_mark = D88_SECTOR_DELETED_MARK_NONE;
  d88_sector_header->status = D88_SECTOR_STATUS_NORMAL;
  d88_sector_header->size_of_data = sector_size;

  return true;
}
