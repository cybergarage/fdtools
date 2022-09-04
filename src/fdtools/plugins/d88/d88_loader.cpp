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

#include <fdtools/plugins/d88/d88.h>
#include <fdtools/util/hexdump.h>

bool fdt_d88_image_load(FdtFileImage*, FILE*);
bool fdt_d88_header_parse(FdtD88Header*, byte_t*);
bool fdt_d88_sector_header_read(FdtD88SectorHeader*, FILE* fp, int n, size_t offset);
bool fdt_d88_sector_header_parse(FdtD88SectorHeader*, int, size_t, byte_t*);
bool fdt_d88_sector_data_read(FdtD88SectorHeader*, FILE* fp, size_t offset, byte_t* buf, size_t buf_size);
bool fdt_image_setd88headerinfo(FdtFileImage* img, FdtD88Header* header);

bool fdt_d88_image_load(FdtFileImage* img, FdtError* err)
{
  if (!img)
    return false;

  fdt_log_debug(FDT_D88_MESSAGE_HEADER "loading %s", fdt_image_getname(img));

  FILE* fp = fdt_image_file_getfile(img);
  if (!fp)
    return false;

  byte_t header_buf[sizeof(FdtD88Header)];
  if (!fdt_file_read(fp, header_buf, sizeof(header_buf))) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  // Read a raw header

  FdtD88Header d88_header;
  if (!fdt_d88_header_parse(&d88_header, header_buf))
    return false;
  if (!fdt_image_setd88headerinfo(img, &d88_header))
    return false;

  size_t d88_image_file_size = sizeof(FdtD88Header);

  for (int n = 0; n < D88_HEADER_NUMBER_OF_SECTOR; n++) {
    size_t sector_header_offset = d88_header.track_offset[n];
    if (sector_header_offset == 0) {
      continue;
    }

    // Read a raw sectors

    FdtD88SectorHeader d88_sector_header;
    if (!fdt_d88_sector_header_read(&d88_sector_header, fp, n, sector_header_offset)) {
      fdt_error_setlasterror(err, "");
      return false;
    }
    d88_image_file_size += sizeof(FdtD88SectorHeader);

    size_t sector_size = d88_sector_header.size_of_data;
    if (sector_size <= 0) {
      switch (d88_sector_header.n) {
      case D88_SECTOR_N_128:
        sector_size = 128;
        break;
      case D88_SECTOR_N_256:
        sector_size = 256;
        break;
      case D88_SECTOR_N_512:
        sector_size = 512;
        break;
      case D88_SECTOR_N_1024:
        sector_size = 1024;
        break;
      }
    }

    size_t number_of_sector = d88_sector_header.number_of_sector;
    size_t sector_data_offset = sector_header_offset + sizeof(FdtD88SectorHeader);

    for (int sector_no = 0; sector_no < number_of_sector; sector_no++) {

      byte_t* sector_data = (byte_t*)malloc(sector_size);
      if (!sector_data) {
        fdt_error_setlasterror(err, FDT_IMAGE_MESSAGE_SECTOR_PRINTF_FORMAT, d88_sector_header.c, d88_sector_header.h, sector_no);
        return false;
      }

      if (!fdt_d88_sector_data_read(&d88_sector_header, fp, sector_data_offset, sector_data, sector_size)) {
        fdt_error_setlasterror(err, FDT_IMAGE_MESSAGE_SECTOR_PRINTF_FORMAT, d88_sector_header.c, d88_sector_header.h, sector_no);
        free(sector_data);
        return false;
      }

      FdtImageSector* sector = fdt_image_sector_new();
      if (!sector) {
        free(sector_data);
        return false;
      }

      fdt_image_sector_settracknumber(sector, d88_sector_header.c);
      fdt_image_sector_setheadnumber(sector, d88_sector_header.h);
      fdt_image_sector_setnumber(sector, sector_no + 1);
      fdt_image_sector_setsize(sector, sector_size);
      fdt_image_sector_setdata(sector, sector_data);

      sector_data_offset += sector_size;
      d88_image_file_size += sector_size;

      fdt_image_addsector(img, sector);

      // fdt_hexdump_print(fdt_image_sector_getdata(sector), fdt_image_sector_getsize(sector));
    }
  }

  fdt_image_setsize(img, d88_image_file_size);
  fdt_image_setnumberoftrack(img, fdt_image_sectors_getnumberoftrack(img->sectors));
  fdt_image_setnumberofhead(img, fdt_image_sectors_getnumberofhead(img->sectors));
  fdt_image_setnumberofsector(img, fdt_image_sectors_getnumberofsector(img->sectors));
  fdt_image_setsectorsize(img, fdt_image_sectors_getmaxsectorsize(img->sectors));

  return true;
}

bool fdt_d88_header_parse(FdtD88Header* header, byte_t* header_buf)
{
  // TODO: Support Big-endian architecture
  memcpy(header, header_buf, sizeof(FdtD88Header));
  fdt_d88_header_log_debug(header);
  return true;
}

bool fdt_image_setd88headerinfo(FdtFileImage* img, FdtD88Header* header)
{
  fdt_image_settarget(img, header->name);
  fdt_image_setsize(img, header->disk_size);
  fdt_image_setwriteprotectenabled(img, header->write_protect ? true : false);

  switch (header->disk_type) {
  case D88_DISK_TYPE_1D:
  case D88_DISK_TYPE_2D:
    fdt_image_setdensity(img, FDT_IMAGE_DENSITY_SD);
    break;
  case D88_DISK_TYPE_1DD:
  case D88_DISK_TYPE_2DD:
    fdt_image_setdensity(img, FDT_IMAGE_DENSITY_DD);
    break;
  case D88_DISK_TYPE_2HD:
    fdt_image_setdensity(img, FDT_IMAGE_DENSITY_HD);
    break;
  }

  return true;
}

bool fdt_d88_sector_header_read(FdtD88SectorHeader* sector, FILE* fp, int n, size_t offset)
{
  if (!fdt_file_seek(fp, offset, SEEK_SET))
    return false;

  byte_t sector_buf[sizeof(FdtD88SectorHeader)];
  if (!fdt_file_read(fp, sector_buf, sizeof(sector_buf)))
    return false;

  if (!fdt_d88_sector_header_parse(sector, n, offset, sector_buf))
    return false;

  return true;
}

bool fdt_d88_sector_header_parse(FdtD88SectorHeader* sector, int n, size_t offset, byte_t* sector_buf)
{
  // TODO: Support Big-endian architecture
  memcpy(sector, sector_buf, sizeof(FdtD88SectorHeader));
  fdt_d88_sector_header_log_debug(sector);
  return true;
}

bool fdt_d88_sector_data_read(FdtD88SectorHeader*, FILE* fp, size_t offset, byte_t* buf, size_t buf_size)
{
  if (!fdt_file_seek(fp, offset, SEEK_SET))
    return false;

  if (!fdt_file_read(fp, buf, buf_size))
    return false;

  return true;
}
