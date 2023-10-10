
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

#include <fdtools/error.h>
#include <fdtools/img/error.h>
#include <fdtools/plugins/fmt/dos/bpb.h>
#include <fdtools/plugins/fmt/dos/fat.h>

FdtFat* fdt_fat_new(void)
{
  FdtFat* fat = (FdtFat*)calloc(sizeof(FdtFat), 1);
  if (!fat)
    return NULL;

  fat->bpb = fdt_fat_bpb_new();
  fat->bpbExt = fdt_fat_bpbex_new();

  if (!fat->bpb || !fat->bpbExt) {
    fdt_fat_delete(fat);
    return NULL;
  }

  return fat;
}

bool fdt_fat_delete(FdtFat* fat)
{
  if (!fat)
    return false;

  if (!fat->bpb) {
    fdt_fat_bpb_delete(fat->bpb);
  }
  if (!fat->bpbExt) {
    fdt_fat_bpbex_delete(fat->bpbExt);
  }

  free(fat);

  return true;
}

bool fdt_fat_loadimage(FdtFat* fat, FdtImage* img, FdtError* err)
{
  if (!fat || !img)
    return false;

  FdtImageSector* boot_sector = fdt_image_getsector(img, 0, 0, 0);
  if (!boot_sector) {
    fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_SECTOR_NOT_FOUND, 0, 0, 0);
    return false;
  }

  return true;
}
