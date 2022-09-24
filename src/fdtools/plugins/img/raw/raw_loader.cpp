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

#include <fdtools/plugins/img/raw/raw.h>

bool fdt_raw_image_autoconfing(FdtFileImage* img, FdtError* err)
{
  if (!img)
    return false;

  FILE* fp = fdt_image_file_getfile(img);
  if (!fp)
    return false;

  if (fseek(fp, 0L, SEEK_END) != 0) {
    fdt_error_setmessage(err, "seek error (SEEK_END)");
    fseek(fp, 0L, SEEK_SET);
    return false;
  }

  size_t img_size = ftell(fp);
  if (fseek(fp, 0L, SEEK_SET) != 0) {
    fdt_error_setmessage(err, "seek error (SEEK_SET)");
    return false;
  }

  FdtImageConfig* config = fdt_image_getconfig(img);
  if (!config)
    return false;

  if (!fdt_image_config_autoparametersbysize(config, img_size)) {
    fdt_error_setmessage(err, "undefined raw image size (%ld)", img_size);
  }

  return true;
}

bool fdt_raw_image_load(FdtFileImage* img, FdtError* err)
{
  if (!img)
    return false;

  if (!fdt_raw_image_autoconfing(img, err)) {
    return false;
  }

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

  size_t total_image_size = 0;

  for (size_t c = 0; c < number_of_cylinder; c++) {
    for (size_t h = 0; h < number_of_head; h++) {
      for (size_t s = 1; s <= number_of_sector; s++) {
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
        fdt_image_sector_setnumber(sector, s);
        fdt_image_sector_setsize(sector, sector_size);
        fdt_image_sector_setdata(sector, sector_data);

        fdt_image_addsector(img, sector);

        total_image_size += sector_size;
      }
    }
  }

  fdt_image_setsize(img, total_image_size);

  return true;
}
