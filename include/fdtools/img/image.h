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

#ifndef _FDTOOLS_IMG_IMAGE_H_
#define _FDTOOLS_IMG_IMAGE_H_

#include <stdio.h>

#include <fdtools/img/config.h>
#include <fdtools/img/sector.h>

#ifdef __cplusplus
extern "C" {
#endif

const int FDT_IMAGE_HEADER_SIGNATURE_MAX = 8;

typedef bool (*FDT_IMAGE_FILELOADERFUNC)(void*, FILE*);

typedef struct {
  FdtImageConfig* config;
  FdtImageSectors* sectors;
  FDT_IMAGE_FILELOADERFUNC load_file;
} FdtImage;

FdtImage* fdt_image_new();
void fdt_image_delete(FdtImage* img);
void fdt_image_print(FdtImage* img);

#define fdt_image_getconfig(img) (img->config)
#define fdt_image_getsectors(img) (img->sectors)

#define fdt_image_setname(img, v) fdt_image_config_setname(img->config, v)
#define fdt_image_setsize(img, v) fdt_image_config_setsize(img->config, v)
#define fdt_image_setdensitytype(img, v) fdt_image_config_setdensitytype(img->config, v)
#define fdt_image_setrpm(img, v) fdt_image_config_setrpm(img->config, v)
#define fdt_image_setnumberofhead(img, v) fdt_image_config_setnumberofhead(img->config, v)
#define fdt_image_setnumberofsector(img, v) fdt_image_config_setnumberofsector(img->config, v)
#define fdt_image_setnumberofcylinder(img, v) fdt_image_config_setnumberofcylinder(img->config, v)
#define fdt_image_setsectorsize(img, v) fdt_image_config_setsectorsize(img->config, v)

#define fdt_image_addsector(img, sector) fdt_list_add((FdtList*)img->sectors, (FdtList*)sector)

bool fdt_image_load(FdtImage*, FILE*);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_IMAGE_H_ */
