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
#include <fdtools/img/file.h>
#include <fdtools/img/hfe.h>
#include <fdtools/util/string.h>

bool fdt_image_file_delete(FdtFileImage*);

FdtImage* fdt_image_file_new()
{
  FdtFileImage* img = (FdtFileImage*)malloc(sizeof(FdtFileImage));
  if (!img) {
    return NULL;
  }

  if (!fdt_image_init((FdtImage*)img)) {
    fdt_image_file_delete(img);
    return NULL;
  }

  img->fp = NULL;
  
  fdt_image_setdestructor(img, fdt_image_file_delete);

  return (FdtImage*)img;
}

bool fdt_image_file_delete(FdtFileImage* img)
{
  return true;
}
