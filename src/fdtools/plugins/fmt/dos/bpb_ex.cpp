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

#include <fdtools/plugins/fmt/dos/bpb.h>
#include <fdtools/plugins/fmt/dos/error.h>

FdtFatBpbExtended* fdt_fat_bpbex_new(void)
{
  FdtFatBpbExtended* bpb = (FdtFatBpbExtended*)calloc(sizeof(FdtFatBpbExtended), 1);
  if (!bpb) {
    return NULL;
  }
  return bpb;
}

bool fdt_fat_bpbex_delete(FdtFatBpbExtended* bpb)
{
  if (!bpb)
    return false;

  free(bpb);

  return true;
}

bool fdt_fat_bpbex_readimagesector(FdtFatBpbExtended* bpb, FdtImageSector* sector, FdtError* err)
{
  if (!bpb || !sector)
    return false;

  size_t cylinder_no = fdt_image_sectors_getnumberofcylinder(sector);
  size_t head_no = fdt_image_sectors_getnumberofhead(sector);
  size_t sector_no = fdt_image_sectors_getnumberofsector(sector);

  if (cylinder_no != 0 || head_no != 0 || sector_no != 0) {
    fdt_error_setmessage(err, FDT_DOS_FAT_BPB_INVALID_SECTOR_NO, cylinder_no, head_no, sector_no);
    return false;
  }

  size_t sector_size = fdt_image_sector_getsize(sector);
  size_t expected_sector_size = sizeof(FdtFatBpb) + sizeof(FdtFatBpbExtended);
  if (sector_size < expected_sector_size) {
    fdt_error_setmessage(err, FDT_DOS_FAT_BPB_INVALID_SECTOR_SIZE, sector_size, expected_sector_size);
    return false;
  }

  memcpy(bpb, fdt_image_sector_getdata(sector), sizeof(FdtFatBpbExtended));

  return true;
}
