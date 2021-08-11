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

#include <fdtools/dev/image.h>
#include <fdtools/img/image.h>
#include <fdtools/plugins/d88/d88.h>
#include <fdtools/plugins/hfe/hfe.h>
#include <fdtools/plugins/raw/raw.h>
#include <fdtools/plugins/plugin.h>

FdtImage* fdt_image_name_new(const char* filename, FdtError* err)
{
  FdtImage* img = fdt_image_name_new_bytype(fdt_image_name_gettype(filename));
  if (!img) {
    fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_UNKNOWN_TYPE_FORMAT, filename);
    return NULL;
  }
  fdt_image_setname(img, filename);
  return img;
}

FdtImage* fdt_image_name_new_byname(const char* filename, FdtError* err)
{
  FdtImage* img = fdt_image_name_new_bytype(fdt_image_name_gettypebyname(filename));
  if (!img) {
    fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_UNKNOWN_TYPE_FORMAT, filename);
    return NULL;
  }
  fdt_image_setname(img, filename);
  return img;
}

FdtImage* fdt_image_name_new_bytype(FdtImageType img_type)
{
  FdtImage* img;

  switch (img_type) {
  case FDT_IMAGE_TYPE_DEV:
    img = fdt_device_image_new();
    break;
  case FDT_IMAGE_TYPE_RAW:
    img = fdt_raw_image_new();
    break;
  case FDT_IMAGE_TYPE_HFE:
    img = fdt_hfe_image_new();
    break;
  case FDT_IMAGE_TYPE_D88:
    img = fdt_d88_image_new();
    break;
  default:
    return NULL;
  }

  return img;
}

bool fdt_image_name_isdevice(const char* filename)
{
  if (!filename || (fdt_strlen(filename) <= 0))
    return false;

  if (!fdt_file_hasprefix(filename, FDT_DEVICE_PREFIX))
    return false;

  return true;
}

FdtImageType fdt_image_name_gettype(const char* filename)
{
  if (!filename || (fdt_strlen(filename) <= 0))
    return FDT_IMAGE_TYPE_UNKNOWN;

  if (fdt_image_name_isdevice(filename))
    return FDT_IMAGE_TYPE_DEV;

  // Identify image file type by the header signature

  FdtImageType file_type = fdt_image_name_gettypebysignature(filename);
  if (file_type != FDT_IMAGE_TYPE_UNKNOWN)
    return file_type;

  // Identify image file type by the filename extention

  return fdt_image_name_gettypebyname(filename);
}

FdtImageType fdt_image_name_gettypebysignature(const char* filename)
{
  if (!filename || (fdt_strlen(filename) <= 0))
    return FDT_IMAGE_TYPE_UNKNOWN;

  // Identify image file type by the header signature

  FILE* fp = fdt_file_open(filename, FDT_FILE_READ);
  if (!fp)
    return FDT_IMAGE_TYPE_UNKNOWN;

  char sig[FDT_IMAGE_HEADER_SIGNATURE_MAX];
  size_t n_read = fread(sig, sizeof(char), FDT_IMAGE_HEADER_SIGNATURE_MAX, fp);
  fdt_file_close(fp);

  if (n_read != FDT_IMAGE_HEADER_SIGNATURE_MAX) {
    return FDT_IMAGE_TYPE_UNKNOWN;
  }

  if (fdt_hfe_image_hassig(NULL, (byte_t*)sig, FDT_IMAGE_HEADER_SIGNATURE_MAX))
    return FDT_IMAGE_TYPE_HFE;

  // Identify image file type by the filename extention

  return FDT_IMAGE_TYPE_UNKNOWN;
}

FdtImageType fdt_image_name_gettypebyname(const char* filename)
{
  if (!filename || (fdt_strlen(filename) <= 0))
    return FDT_IMAGE_TYPE_UNKNOWN;

  if (fdt_image_name_isdevice(filename))
    return FDT_IMAGE_TYPE_DEV;

  if (fdt_d88_image_hasext(NULL, filename))
    return FDT_IMAGE_TYPE_D88;

  if (fdt_raw_image_hasext(NULL, filename))
    return FDT_IMAGE_TYPE_RAW;

  return FDT_IMAGE_TYPE_UNKNOWN;
}