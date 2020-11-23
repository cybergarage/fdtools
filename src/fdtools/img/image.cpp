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
  FdtImage* img = (FdtImage*)malloc(sizeof(FdtImage));
  if (!img) {
    return NULL;
  }

  img->config = fdt_image_config_new();
  img->sectors = fdt_image_sectors_new();

  if (!img->config || !img->config) {
    fdt_image_delete(img);
    return NULL;
  }

  return img;
}

void fdt_image_delete(FdtImage* img)
{
  if (img->config)
    fdt_image_config_delete(img->config);
  if (img->sectors)
    fdt_image_sectors_delete(img->sectors);

  free(img);
}

bool fdt_image_load(FdtImage* img, FILE* fp)
{
  if (!img || !fp)
    return false;
  return img->load_file(img, fp);
}

void fdt_image_print(FdtImage* img)
{
  if (img->config)
    fdt_image_config_print(img->config);
  if (img->sectors)
    fdt_image_sectors_print(img->sectors);
}
