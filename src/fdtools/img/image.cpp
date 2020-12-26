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
  if (!fdt_image_clear(img))
    return false;
  free(img);
  return true;
}

bool fdt_image_clear(FdtImage* img)
{
  if (!img)
    return false;

  if (img->image_destructor) {
    if (!img->image_destructor(img))
      return false;
  }

  if (img->config) {
    fdt_image_config_delete(img->config);
  }
  if (img->sectors) {
    fdt_image_sectors_delete(img->sectors);
  }

  return true;
}

bool fdt_image_load(FdtImage* img, FILE* fp, FdtError* err)
{
  if (!img || !fp)
    return false;
  return img->image_loader(img, fp, err);
}

bool fdt_image_export(FdtImage* img, FILE* fp, FdtError* err)
{
  if (!img || !fp)
    return false;
  return img->image_exporter(img, fp, err);
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
