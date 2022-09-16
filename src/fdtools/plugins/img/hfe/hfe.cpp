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

#include <fdtools/plugins/img/hfe/hfe.h>

FdtImage* fdt_hfe_image_new(void)
{
  FdtImage* img = fdt_image_file_new();
  if (!img)
    return NULL;

  fdt_image_setgettypeid(img, fdt_hfe_image_gettypeid);
  fdt_image_sethassig(img, fdt_hfe_image_hassig);
  fdt_image_setloader(img, fdt_hfe_image_load);
  fdt_image_setexporter(img, fdt_hfe_image_export);

  return img;
}

const char* fdt_hfe_image_gettypeid(FdtImage* img)
{
  return "HFE";
}

bool fdt_hfe_image_hassig(FdtFileImage* img, byte_t* header, size_t header_size)
{
  if (header_size < fdt_strlen(HFE_IMAGE_HEADER_SIGNATURE))
    return false;
  if (fdt_strncmp((char*)header, HFE_IMAGE_HEADER_SIGNATURE, fdt_strlen(HFE_IMAGE_HEADER_SIGNATURE)) == 0)
    return true;
  return false;
}
