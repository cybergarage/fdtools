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

#include <fdtools/img/raw.h>
#include <fdtools/util/file.h>
#include <fdtools/util/hexdump.h>
#include <fdtools/util/string.h>

bool fdt_raw_image_load(FdtFileImage* img, FdtError* err)
{
  if (!img)
    return false;

  FILE* fp = fdt_image_file_getfile(img);
  if (!fp)
    return false;

  FdtImageConfig* config = fdt_image_getconfig(img);
  if (!config)
    return false;

  if (!fdt_image_config_isvalid(config, err))
    return false;

  size_t number_of_cylinder = fdt_image_config_getnumberofcylinder(config);
  size_t number_of_head = fdt_image_config_getnumberofhead(config);
  size_t number_of_sector = fdt_image_config_getnumberofsector(config);
  size_t sector_size = fdt_image_config_getsectorsize(config);

  for (size_t c = 0; c < number_of_cylinder; c++) {
    for (size_t h = 0; h < number_of_head; h++) {
      for (size_t s = 0; s < number_of_sector; s++) {
        byte_t* sector_data = (byte_t*)malloc(sector_size);
        if (!sector_data) {
          return false;
        }

        if (!fdt_file_read(fp, sector_data, sector_size)) {
          fdt_error_setlasterror(err, "");
          free(sector_data);
          return false;
        }

        FdtImageSector* sector = fdt_image_sector_new();
        if (!sector) {
          free(sector_data);
          return false;
        }

        fdt_image_sector_setcylindernumber(sector, c);
        fdt_image_sector_setheadnumber(sector, h);
        fdt_image_sector_setnumber(sector, s + 1);
        fdt_image_sector_setsize(sector, sector_size);
        fdt_image_sector_setdata(sector, sector_data);

        fdt_image_addsector(img, sector);
      }
    }
  }

  return true;
}
