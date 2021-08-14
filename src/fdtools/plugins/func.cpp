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
#include <fdtools/plugins/image.h>
#include <fdtools/plugins/loader.h>
#include <fdtools/plugins/plugin.h>
#include <fdtools/plugins/raw/raw.h>

bool fdt_image_name_isdevice(const char* filename)
{
  if (!filename || (fdt_strlen(filename) <= 0))
    return false;

  if (!fdt_file_hasprefix(filename, FDT_DEVICE_PREFIX))
    return false;

  return true;
}

FDT_IMAGE_IMAGER fdt_image_plugins_getimagerbysignature(const char* filename)
{
  if (!filename || (fdt_strlen(filename) <= 0))
    return NULL;

  FILE* fp = fdt_file_open(filename, FDT_FILE_READ);
  if (!fp)
    return NULL;

  char sig[FDT_IMAGE_HEADER_SIGNATURE_MAX];
  size_t n_read = fread(sig, sizeof(char), FDT_IMAGE_HEADER_SIGNATURE_MAX, fp);
  fdt_file_close(fp);

  if (n_read != FDT_IMAGE_HEADER_SIGNATURE_MAX) {
    return NULL;
  }

  for (FdtImagePlugin* plg = fdt_image_plugins_getallimagers(); plg; plg = fdt_image_plugin_next(plg)) {
    FdtImage* img = fdt_image_plugin_createimage(plg);
    if (fdt_image_hassig(img, (byte_t*)&sig, n_read)) {
      fdt_image_delete(img);
      return fdt_image_plugin_getimager(plg);
    }
    fdt_image_delete(img);
  }

  return NULL;
}

FDT_IMAGE_IMAGER fdt_image_plugins_getimagerbyextention(const char* filename)
{
  for (FdtImagePlugin* plg = fdt_image_plugins_getallimagers(); plg; plg = fdt_image_plugin_next(plg)) {
    FdtImage* img = fdt_image_plugin_createimage(plg);
    if (fdt_image_hasext(img, filename)) {
      fdt_image_delete(img);
      return fdt_image_plugin_getimager(plg);
    }
    fdt_image_delete(img);
  }
  return NULL;
}

FDT_IMAGE_IMAGER fdt_image_plugins_getimagerbyfile(const char* filename, FdtError* err)
{
  if (!filename || (fdt_strlen(filename) <= 0))
    return NULL;

  if (fdt_image_name_isdevice(filename))
    return fdt_device_image_new;

  FDT_IMAGE_IMAGER imager;
  imager = fdt_image_plugins_getimagerbysignature(filename);
  if (imager)
    return imager;

  imager = fdt_image_plugins_getimagerbyextention(filename);
  if (imager)
    return imager;

  return NULL;
}

FDT_IMAGE_IMAGER fdt_image_plugins_getimager(const char* filename, FdtError* err)
{
  if (!filename || (fdt_strlen(filename) <= 0))
    return NULL;

  FDT_IMAGE_IMAGER imager = fdt_image_plugins_getimagerbyfile(filename, err);
  if (!imager) {
    fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_UNKNOWN_TYPE_FORMAT, filename);
    return NULL;
  }
  return imager;
}

FdtImage* fdt_image_plugins_create(const char* filename, FdtError* err)
{
  if (!filename || (fdt_strlen(filename) <= 0))
    return NULL;

  FDT_IMAGE_IMAGER imager = fdt_image_plugins_getimager(filename, err);
  if (!imager)
    return NULL;

  FdtImage* img = imager();
  fdt_image_settarget(img, filename);
  return img;
}
