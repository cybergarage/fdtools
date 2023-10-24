
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

#include <fdtools/plugins/fmt/dos/dos.h>
#include <fdtools/plugins/fmt/dos/sector.h>

bool fdt_dos_formatbootsector(FdtFormat* fmt, FdtError* err)
{
  FdtImage* img = fdt_format_getimage(fmt);
  if (!img)
    return false;

  FdtImageSector* boot_sector = fdt_image_getsector(img, 0, 0, 1);
  if (!boot_sector) {
    fdt_error_setmessage(err, "boot sector is not found");
    return false;
  }

  if (fdt_image_sector_getsize(boot_sector) < sizeof(FdtFatBpb)) {
    fdt_error_setmessage(err, "boot sector size is too small");
    return false;
  }

  FdtFatBpb* bpb = fdt_fat_bpb_from(fdt_image_sector_getdata(boot_sector));

  return true;
}
