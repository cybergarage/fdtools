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

#include <fdtools/plugins/fmt/x68/x68.h>
#include <fdtools/plugins/image.h>

FdtImage* fdt_x68_floppy_image_new(void)
{
  FdtImage* img = fdt_image_new();
  if (!img)
    return NULL;

  fdt_image_setnumberofcylinder(img, FDT_X68_FD_CYLINDER);
  fdt_image_setnumberofhead(img, FDT_X68_FD_HEAD);
  fdt_image_setnumberofsector(img, FDT_X68_FD_SECTOR);
  fdt_image_setsectorsize(img, FDT_X68_FD_SECTOR_SIZE);

  return img;
}

FdtImage* fdt_x68_floppy_image_from(const char* target, FdtError* err)
{
  FdtImage* img = fdt_image_from(target, err);
  if (!img)
    return NULL;
  return img;
}

bool fdt_x68_image_isfloppy(FdtImage* img)
{
  if (!img)
    return false;

  if (fdt_image_getnumberofcylinder(img) != FDT_X68_FD_CYLINDER)
    return false;

  if (fdt_image_getnumberofhead(img) != FDT_X68_FD_HEAD)
    return false;

  if (fdt_image_getnumberofsector(img) != FDT_X68_FD_SECTOR)
    return false;

  if (fdt_image_getsectorsize(img) != FDT_X68_FD_SECTOR_SIZE)
    return false;

  return true;
}

bool fdt_x68_image_generate(FdtImage* img)
{
  if (!fdt_image_generatesectors(img, NULL))
    return false;
  return true;
}

bool fdt_x68_image_delete(FdtImage* img)
{
  return fdt_image_delete(img);
}
