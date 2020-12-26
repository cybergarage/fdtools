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

#include <fdtools/error.h>
#include <fdtools/img/config.h>
#include <fdtools/img/sector.h>
#include <fdtools/util/file.h>

#ifdef __cplusplus
extern "C" {
#endif

const int FDT_IMAGE_HEADER_SIGNATURE_MAX = 8;

#define FDT_IMAGE_STRUCT_MEMBERS     \
  FdtImageConfig* config;            \
  FdtImageSectors* sectors;          \
  FDT_IMAGE_OPENER image_opener;     \
  FDT_IMAGE_CLOSER image_closer;     \
  FDT_IMAGE_LOADER image_loader;     \
  FDT_IMAGE_EXPORTER image_exporter; \
  FDT_IMAGE_DESTRUCTOR image_destructor;

typedef bool (*FDT_IMAGE_OPENER)(void*, const char*, FdtFileMode, FdtError*);
typedef bool (*FDT_IMAGE_CLOSER)(void*, FdtError*);
typedef bool (*FDT_IMAGE_LOADER)(void*, FdtError*);
typedef bool (*FDT_IMAGE_EXPORTER)(void*, FdtError*);
typedef bool (*FDT_IMAGE_DESTRUCTOR)(void*);

typedef struct FDT_ATTR_PACKED {
  FDT_IMAGE_STRUCT_MEMBERS
} FdtImage;

FdtImage* fdt_image_new();
bool fdt_image_delete(FdtImage*);

bool fdt_image_init(FdtImage*);
bool fdt_image_clear(FdtImage*);

bool fdt_image_open(FdtImage*, const char*, FdtFileMode, FdtError*);
bool fdt_image_close(FdtImage*, FdtError*);
bool fdt_image_load(FdtImage*, FdtError*);
bool fdt_image_export(FdtImage*, FdtError*);

bool fdt_image_equals(FdtImage*, FdtImage*);

void fdt_image_print(FdtImage* img);

#define fdt_image_getconfig(img) (img->config)
#define fdt_image_getsectors(img) (img->sectors)

#define fdt_image_setopener(img, fn) (img->image_opener = (FDT_IMAGE_OPENER)fn)
#define fdt_image_setcloser(img, fn) (img->image_closer = (FDT_IMAGE_CLOSER)fn)
#define fdt_image_setloader(img, fn) (img->image_loader = (FDT_IMAGE_LOADER)fn)
#define fdt_image_setexporter(img, fn) (img->image_exporter = (FDT_IMAGE_EXPORTER)fn)
#define fdt_image_setdestructor(img, fn) (img->image_destructor = (FDT_IMAGE_DESTRUCTOR)fn)

#define fdt_image_setname(img, v) fdt_image_config_setname(img->config, v)
#define fdt_image_setsize(img, v) fdt_image_config_setsize(img->config, v)
#define fdt_image_setdensity(img, v) fdt_image_config_setdensity(img->config, v)
#define fdt_image_setnumberofhead(img, v) fdt_image_config_setnumberofhead(img->config, v)
#define fdt_image_setnumberofsector(img, v) fdt_image_config_setnumberofsector(img->config, v)
#define fdt_image_setnumberofcylinder(img, v) fdt_image_config_setnumberofcylinder(img->config, v)
#define fdt_image_setsectorsize(img, v) fdt_image_config_setsectorsize(img->config, v)
#define fdt_image_setrpm(img, v) fdt_image_config_setrpm(img->config, v)
#define fdt_image_setwriteprotect(img, v) fdt_image_config_setwriteprotect(img->config, v)

#define fdt_image_hasname(img) fdt_image_config_hasname(img->config)
#define fdt_image_getname(img) fdt_image_config_getname(img->config)
#define fdt_image_getsize(img) fdt_image_config_getsize(img->config)
#define fdt_image_getdensity(img) fdt_image_config_getdensity(img->config)
#define fdt_image_getnumberofhead(img) fdt_image_config_getnumberofhead(img->config)
#define fdt_image_getnumberofsector(img) fdt_image_config_getnumberofsector(img->config)
#define fdt_image_getnumberofcylinder(img) fdt_image_config_getnumberofcylinder(img->config)
#define fdt_image_getsectorsize(img) fdt_image_config_getsectorsize(img->config)
#define fdt_image_getrpm(img) fdt_image_config_getrpm(img->config)
#define fdt_image_getwriteprotect(img) fdt_image_config_getwriteprotect(img->config)
#define fdt_image_calculaterawsize(img) fdt_image_config_calculaterawsize(img->config)

#define fdt_image_getsector(img, c, h, r) fdt_image_sectors_getsector(img->sectors, c, h, r)
#define fdt_image_getnumberoftracksector(img, c, h) fdt_image_sectors_getnumberoftracksector(img->sectors, c, h)
#define fdt_image_gettracksize(img, c, h) fdt_image_sectors_gettracksize(img->sectors, c, h)

#define fdt_image_addsector(img, sector) fdt_list_add((FdtList*)img->sectors, (FdtList*)sector)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_IMAGE_H_ */
