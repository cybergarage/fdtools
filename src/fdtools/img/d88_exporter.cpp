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
#include <fdtools/util/file.h>
#include <fdtools/util/string.h>

bool fdt_d88_image_export(FdtFileImage* img, FdtError* err)
{
  if (!img)
    return false;

  FILE* fp = fdt_image_file_getfile(img);
  if (!fp)
    return false;

  FdtD88Header d88_header;
  if (!fdt_d88_header_setconfig(&d88_header, (FdtImage*)img, err))
    return false;

  if (!fdt_file_write(fp, &d88_header, sizeof(d88_header))) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  FdtImageDensity img_density = fdt_image_getsupposeddensity(img);
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
