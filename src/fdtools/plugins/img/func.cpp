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
#include <fdtools/plugins/image.h>
#include <fdtools/plugins/img/d88/d88.h>
#include <fdtools/plugins/img/hfe/hfe.h>
#include <fdtools/plugins/img/loader.h>
#include <fdtools/plugins/img/plugin.h>
#include <fdtools/plugins/img/raw/raw.h>

bool fdt_image_name_isdevice(const char* filename)
{
  if (!filename || (fdt_strlen(filename) <= 0))
    return false;

  if (!fdt_file_hasprefix(filename, FDT_DEVICE_PREFIX))
    return false;

  return true;
}

void fdt_image_plugins_getallextentions(FdtStrings* exts)
{
  for (FdtImagePlugin* plg = fdt_image_getimagers(); plg; plg = fdt_image_plugin_next(plg)) {
    FdtImage* img = fdt_image_plugin_createimage(plg);
    fdt_image_getextentions(img, exts);
    fdt_image_delete(img);
  }
}

FDT_IMAGE_IMAGER fdt_image_getfileimagerbysignature(const char* filename)
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

  for (FdtImagePlugin* plg = fdt_image_getimagers(); plg; plg = fdt_image_plugin_next(plg)) {
    FdtImage* img = fdt_image_plugin_createimage(plg);
    if (fdt_image_hassig(img, (byte_t*)&sig, n_read)) {
      fdt_image_delete(img);
      return fdt_image_plugin_getimager(plg);
    }
    fdt_image_delete(img);
  }

  return NULL;
}

FDT_IMAGE_IMAGER fdt_image_getfileimagerbyextention(const char* filename)
{
  for (FdtImagePlugin* plg = fdt_image_getimagers(); plg; plg = fdt_image_plugin_next(plg)) {
    FdtImage* img = fdt_image_plugin_createimage(plg);
    if (fdt_image_hasext(img, filename)) {
      fdt_image_delete(img);
      return fdt_image_plugin_getimager(plg);
    }
    fdt_image_delete(img);
  }
  return NULL;
}

FDT_IMAGE_IMAGER fdt_image_getfileimager(const char* filename, FdtError* err)
{
  if (!filename || (fdt_strlen(filename) <= 0))
    return NULL;

  if (fdt_image_name_isdevice(filename))
    return fdt_device_image_new;

  FDT_IMAGE_IMAGER imager;
  imager = fdt_image_getfileimagerbysignature(filename);
  if (imager)
    return imager;

  imager = fdt_image_getfileimagerbyextention(filename);
  if (imager)
    return imager;

  return NULL;
}

FDT_IMAGE_IMAGER fdt_image_getimager(const char* target, FdtError* err)
{
  if (!target || (fdt_strlen(target) <= 0))
    return NULL;

  FDT_IMAGE_IMAGER imager = fdt_image_getfileimager(target, err);
  if (!imager) {
    fdt_error_setmessage(err, FDT_IMAGE_MESSAGE_UNKNOWN_TYPE_FORMAT, target);
    return NULL;
  }
  return imager;
}

FdtImage* fdt_image_from(const char* target, FdtError* err)
{
  if (!target || (fdt_strlen(target) <= 0))
    return NULL;

  FDT_IMAGE_IMAGER imager = fdt_image_getimager(target, err);
  if (!imager)
    return NULL;

  FdtImage* img = imager();
  fdt_image_settarget(img, target);
  return img;
}
