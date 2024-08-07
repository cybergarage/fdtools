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
#include <fdtools/typedef.h>
#include <fdtools/util/file.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  FDT_IMAGE_TYPE_UNKNOWN,
  FDT_IMAGE_TYPE_DEV,
  FDT_IMAGE_TYPE_FILE,
} FdtImageType;

const int FDT_IMAGE_HEADER_SIGNATURE_MAX = 8;

typedef FdtImageType (*FDT_IMAGE_GETTYPE)(void*);
typedef const char* (*FDT_IMAGE_GETTYPEID)(void*);
typedef bool (*FDT_IMAGE_GETEXTENTIONS)(void*, FdtStrings*);
typedef bool (*FDT_IMAGE_HASSIG)(void*, byte_t*, size_t);
typedef bool (*FDT_IMAGE_OPENER)(void*, const char*, FdtFileMode, FdtError*);
typedef bool (*FDT_IMAGE_CLOSER)(void*, FdtError*);
typedef bool (*FDT_IMAGE_ISOPENED)(void*);
typedef bool (*FDT_IMAGE_LOADER)(void*, FdtError*);
typedef bool (*FDT_IMAGE_EXPORTER)(void*, FdtError*);
typedef bool (*FDT_IMAGE_DESTRUCTOR)(void*);

#define FDT_IMAGE_STRUCT_MEMBERS               \
  FdtString* target;                           \
  FdtImageConfig* config;                      \
  FdtImageSectors* sectors;                    \
  FDT_IMAGE_GETTYPE image_gettype;             \
  FDT_IMAGE_GETTYPEID image_gettypeid;         \
  FDT_IMAGE_GETEXTENTIONS image_getextentions; \
  FDT_IMAGE_HASSIG image_hassig;               \
  FDT_IMAGE_OPENER image_opener;               \
  FDT_IMAGE_CLOSER image_closer;               \
  FDT_IMAGE_ISOPENED image_isopened;           \
  FDT_IMAGE_LOADER image_loader;               \
  FDT_IMAGE_EXPORTER image_exporter;           \
  FDT_IMAGE_DESTRUCTOR image_destructor;

typedef struct FDT_ATTR_PACKED {
  FDT_IMAGE_STRUCT_MEMBERS
} FdtImage;

typedef FdtImage* (*FDT_IMAGE_IMAGER)(void);

FdtImage* fdt_image_new();
bool fdt_image_delete(FdtImage*);

bool fdt_image_init(FdtImage*);
bool fdt_image_clear(FdtImage*);

FdtImageType fdt_image_gettype(FdtImage*);
const char* fdt_image_gettypeid(FdtImage*);
bool fdt_image_getextentions(FdtImage*, FdtStrings*);
bool fdt_image_hasext(FdtImage*, const char*);
bool fdt_image_hassig(FdtImage*, byte_t*, size_t);
bool fdt_image_open(FdtImage*, const char*, FdtFileMode, FdtError*);
bool fdt_image_close(FdtImage*, FdtError*);
bool fdt_image_isopened(FdtImage*);
bool fdt_image_load(FdtImage*, FdtError*);
bool fdt_image_import(FdtImage*, FdtImage*, FdtError*);
bool fdt_image_export(FdtImage*, FdtError*);

bool fdt_image_isvalid(FdtImage*, FdtError*);
bool fdt_image_generatesectors(FdtImage*, FdtError*);
off_t fdt_image_getsectoroffset(FdtImage*, FdtImageSector*);
bool fdt_image_equals(FdtImage*, FdtImage*, FdtError*);

void fdt_image_print(FdtImage* img);

#define fdt_image_getconfig(img) (img->config)

#define fdt_image_setgettype(img, fn) (img->image_gettype = (FDT_IMAGE_GETTYPE)fn)
#define fdt_image_setgettypeid(img, fn) (img->image_gettypeid = (FDT_IMAGE_GETTYPEID)fn)
#define fdt_image_setgetextentions(img, fn) (img->image_getextentions = (FDT_IMAGE_GETEXTENTIONS)fn)
#define fdt_image_sethassig(img, fn) (img->image_hassig = (FDT_IMAGE_HASSIG)fn)
#define fdt_image_setopener(img, fn) (img->image_opener = (FDT_IMAGE_OPENER)fn)
#define fdt_image_setcloser(img, fn) (img->image_closer = (FDT_IMAGE_CLOSER)fn)
#define fdt_image_setopenchecker(img, fn) (img->image_isopened = (FDT_IMAGE_ISOPENED)fn)
#define fdt_image_setloader(img, fn) (img->image_loader = (FDT_IMAGE_LOADER)fn)
#define fdt_image_setexporter(img, fn) (img->image_exporter = (FDT_IMAGE_EXPORTER)fn)
#define fdt_image_setdestructor(img, fn) (img->image_destructor = (FDT_IMAGE_DESTRUCTOR)fn)

#define fdt_image_settarget(img, v) fdt_string_setvalue(img->target, v)
#define fdt_image_setname(img, v) fdt_image_config_setname(img->config, v)
#define fdt_image_setsize(img, v) fdt_image_config_setsize(img->config, v)
#define fdt_image_setdensity(img, v) fdt_image_config_setdensity(img->config, v)
#define fdt_image_setnumberofhead(img, v) fdt_image_config_setnumberofhead(img->config, v)
#define fdt_image_setnumberofsector(img, v) fdt_image_config_setnumberofsector(img->config, v)
#define fdt_image_setnumberofcylinder(img, v) fdt_image_config_setnumberofcylinder(img->config, v)
#define fdt_image_setsectorsize(img, v) fdt_image_config_setsectorsize(img->config, v)
#define fdt_image_setbitrate(img, v) fdt_image_config_setbitrate(img->config, v)
#define fdt_image_setrpm(img, v) fdt_image_config_setrpm(img->config, v)
#define fdt_image_setwriteprotectenabled(img, v) fdt_image_config_setwriteprotectenabled(img->config, v)

#define fdt_image_isdevice(img) ((fdt_image_gettype(img) == FDT_IMAGE_TYPE_DEV) ? true : false)
#define fdt_image_gettarget(img) fdt_string_getvalue(img->target)
#define fdt_image_hasname(img) fdt_image_config_hasname(img->config)
#define fdt_image_getname(img) fdt_image_config_getname(img->config)
#define fdt_image_getsize(img) fdt_image_config_getsize(img->config)
#define fdt_image_getdensity(img) fdt_image_config_getdensity(img->config)
#define fdt_image_getsupposeddensity(img) fdt_image_config_getsupposeddensity(img->config)
#define fdt_image_getdensitystring(img) fdt_image_config_getdensitystring(img->config)
#define fdt_image_getnumberofhead(img) fdt_image_config_getnumberofhead(img->config)
#define fdt_image_getnumberofsector(img) fdt_image_config_getnumberofsector(img->config)
#define fdt_image_getnumberofcylinder(img) fdt_image_config_getnumberofcylinder(img->config)
#define fdt_image_getsectorsize(img) fdt_image_config_getsectorsize(img->config)
#define fdt_image_getbitrate(img) fdt_image_config_getbitrate(img->config)
#define fdt_image_getrpm(img) fdt_image_config_getrpm(img->config)
#define fdt_image_iswriteprotectenabled(img) fdt_image_config_iswriteprotectenabled(img->config)
#define fdt_image_calculaterawsize(img) fdt_image_config_calculaterawsize(img->config)

#define fdt_image_getsectors(img) fdt_image_sectors_gets(img->sectors)
#define fdt_image_getsector(img, c, h, r) fdt_image_sectors_getsector(img->sectors, c, h, r)
#define fdt_image_getnumberofcylindersector(img, c, h) fdt_image_sectors_getnumberofcylindersector(img->sectors, c, h)
#define fdt_image_gettracksize(img, c, h) fdt_image_sectors_gettracksize(img->sectors, c, h)
#define fdt_image_gettrackbytes(img, c, h) fdt_image_sectors_gettrackbytes(img->sectors, c, h)
#define fdt_image_getnsectors(img) fdt_image_sectors_size(img->sectors)
#define fdt_image_sectors_geterrorsector(img) fdt_image_sectors_geterrorsector(img->sectors)
#define fdt_image_getnerrorsectors(img) fdt_image_sectors_getnerrorsectors(img->sectors)

#define fdt_image_addsector(img, sector) fdt_list_add((FdtList*)img->sectors, (FdtListNode*)sector)
#define fdt_image_issectorssorted(img) fdt_image_sectors_issorted(img->sectors)
#define fdt_image_sortsectors(img) fdt_image_sectors_sort(img->sectors)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_IMAGE_H_ */
