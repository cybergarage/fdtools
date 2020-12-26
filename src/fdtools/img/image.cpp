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

#include <fdtools/img/image.h>

FdtImage* fdt_image_new()
{
  FdtImage* img = (FdtImage*)calloc(sizeof(FdtImage), 1);
  if (!img) {
    return NULL;
  }

  if (!fdt_image_init(img)) {
    fdt_image_delete(img);
    return NULL;
  }

  return img;
}

bool fdt_image_init(FdtImage* img)
{
  img->config = fdt_image_config_new();
  img->sectors = fdt_image_sectors_new();

  if (!img->config || !img->config) {
    return false;
  }

  return true;
}

bool fdt_image_delete(FdtImage* img)
{
  if (img->image_destructor)
    return img->image_destructor(img);
  free(img);
  return true;
}

bool fdt_image_clear(FdtImage* img)
{
  if (!img)
    return false;

  if (img->config) {
    fdt_image_config_delete(img->config);
  }
  if (img->sectors) {
    fdt_image_sectors_delete(img->sectors);
  }

  return true;
}

bool fdt_image_open(FdtImage* img, const char* name, FdtFileMode mode, FdtError* err)
{
  if (!img)
    return false;
  return img->image_opener(img, name, mode, err);
}

bool fdt_image_close(FdtImage* img, FdtError* err)
{
  if (!img)
    return false;
  return img->image_closer(img, err);
}

bool fdt_image_load(FdtImage* img, FdtError* err)
{
  if (!img)
    return false;
  return img->image_loader(img, err);
}

bool fdt_image_export(FdtImage* img, FdtError* err)
{
  if (!img)
    return false;
  return img->image_exporter(img, err);
}

bool fdt_image_generatesectors(FdtImage* img)
{
  if (!img)
    return false;

  if (!fdt_image_config_isvalid(img->config))
    return false;

  size_t number_of_cylinder = fdt_image_getnumberofcylinder(img);
  size_t number_of_head = fdt_image_getnumberofhead(img);
  size_t number_of_sector = fdt_image_getnumberofsector(img);
  size_t sector_size = fdt_image_getsectorsize(img);

  for (size_t c = 0; c < number_of_cylinder; c++) {
    for (size_t h = 0; h < number_of_head; h++) {
      for (size_t s = 0; s < number_of_sector; s++) {
        FdtImageSector* sector = fdt_image_sector_new();
        if (!sector) {
          return false;
        }
        fdt_image_sector_setcylindernumber(sector, c);
        fdt_image_sector_setheadnumber(sector, h);
        fdt_image_sector_setnumber(sector, s);
        fdt_image_sector_setsize(sector, sector_size);
        fdt_image_addsector(img, sector);
      }
    }
  }

  return true;
}

bool fdt_image_equals(FdtImage* img, FdtImage* other)
{
  if (!img || !other)
    return false;
  if (!fdt_image_config_equals(img->config, other->config))
    return false;
  if (!fdt_image_sectors_equals(img->sectors, other->sectors))
    return false;
  return true;
}

void fdt_image_print(FdtImage* img)
{
  if (img->config)
    fdt_image_config_print(img->config);
  if (img->sectors)
    fdt_image_sectors_print(img->sectors);
}
