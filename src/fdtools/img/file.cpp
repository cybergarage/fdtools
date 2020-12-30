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

#include <fdtools/img/file.h>
#include <fdtools/util/string.h>

bool fdt_image_file_open(FdtFileImage*, const char*, FdtFileMode, FdtError*);
bool fdt_image_file_close(FdtFileImage*, FdtError*);
bool fdt_image_file_isopened(FdtFileImage*);
bool fdt_image_file_delete(FdtFileImage*);

FdtImage* fdt_image_file_new()
{
  FdtFileImage* img = (FdtFileImage*)calloc(sizeof(FdtFileImage), 1);
  if (!img) {
    return NULL;
  }

  if (!fdt_image_init((FdtImage*)img)) {
    fdt_image_file_delete(img);
    return NULL;
  }

  img->fp = NULL;

  fdt_image_setopener(img, fdt_image_file_open);
  fdt_image_setcloser(img, fdt_image_file_close);
  fdt_image_setopenchecker(img, fdt_image_file_isopened);
  fdt_image_setdestructor(img, fdt_image_file_delete);

  return (FdtImage*)img;
}

bool fdt_image_file_delete(FdtFileImage* img)
{
  if (!img)
    return false;
  if (!fdt_image_clear((FdtImage*)img))
    return false;
  return true;
}

bool fdt_image_file_open(FdtFileImage* img, const char* name, FdtFileMode mode, FdtError* err)
{
  if (!img)
    return false;

  img->fp = fdt_file_open(name, mode);
  if (!img->fp) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  return true;
}

bool fdt_image_file_close(FdtFileImage* img, FdtError* err)
{
  if (!img)
    return false;

  if (!img->fp)
    return true;

  if (!fdt_file_close(img->fp)) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  img->fp = NULL;

  return true;
}

bool fdt_image_file_isopened(FdtFileImage* img)
{
  if (!img)
    return false;
  return (img->fp ? true : false);
}
