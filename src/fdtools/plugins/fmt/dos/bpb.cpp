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
#include <fdtools/plugins/fmt/dos/fat.h>

FdtFatBpb* fdt_fat_bpb_new(void)
{
  FdtFatBpb* bpb = (FdtFatBpb*)calloc(sizeof(FdtFatBpb), 1);
  if (!bpb) {
    return NULL;
  }
  return bpb;
}

FdtFatBpb* fdt_fat_bpb_from(byte_t* b)
{
  return (FdtFatBpb*)b;
}

bool fdt_fat_bpb_delete(FdtFatBpb* bpb)
{
  if (!bpb)
    return false;

  free(bpb);

  return true;
}

bool fdt_fat_bpb_loadimagesector(FdtFatBpb* bpb, FdtImageSector* sector, FdtError* err)
{
  if (!bpb || !sector)
    return false;

  if (!fdt_fat_isbootimagesector(sector)) {
    return false;
  }

  size_t sector_size = fdt_image_sector_getsize(sector);
  size_t expected_sector_size = sizeof(FdtFatBpb);
  if (sector_size < expected_sector_size) {
    fdt_error_setmessage(err, FDT_DOS_FAT_BPB_INVALID_SECTOR_SIZE, sector_size, expected_sector_size);
    return false;
  }

  memcpy(bpb, fdt_image_sector_getdata(sector), expected_sector_size);

  return true;
}
