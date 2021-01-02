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

#ifndef _FDTOOLS_IMG_CONFIG_H_
#define _FDTOOLS_IMG_CONFIG_H_

#include <stdlib.h>

#include <fdtools/error.h>
#include <fdtools/typedef.h>
#include <fdtools/util/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  FDT_IMAGE_DENSITY_UNKNOWN = 0,
  FDT_IMAGE_DENSITY_SD = 1,
  FDT_IMAGE_DENSITY_DD = 2,
  FDT_IMAGE_DENSITY_HD = 3,
  FDT_IMAGE_DENSITY_QD = 4,
  FDT_IMAGE_DENSITY_ED = 5,
} FdtImageDensity;

const char* fdt_image_density_getstring(FdtImageDensity);

typedef struct FDT_ATTR_PACKED {
  FdtString* name;
  FdtString* desc;
  FdtImageDensity density;
  size_t size;
  size_t number_of_head;
  size_t number_of_sector;
  size_t number_of_cylinder;
  size_t sector_size;
  int rpm;
  bool write_protect;
} FdtImageConfig;

FdtImageConfig* fdt_image_config_new();
bool fdt_image_config_delete(FdtImageConfig*);

bool fdt_image_config_isvalid(FdtImageConfig*, FdtError*);
FdtImageConfig* fdt_image_config_copy(FdtImageConfig*);
bool fdt_image_config_equals(FdtImageConfig*, FdtImageConfig*, FdtError*);

size_t fdt_image_config_calculaterawsize(FdtImageConfig*);
const char* fdt_image_config_getdescription(FdtImageConfig*);
void fdt_image_config_print(FdtImageConfig*);

#define fdt_image_config_setname(config, v) fdt_string_setvalue(config->name, v)
#define fdt_image_config_setsize(config, v) (config->size = v)
#define fdt_image_config_setdensity(config, v) (config->density = v)
#define fdt_image_config_setnumberofhead(config, v) (config->number_of_head = v)
#define fdt_image_config_setnumberofsector(config, v) (config->number_of_sector = v)
#define fdt_image_config_setnumberofcylinder(config, v) (config->number_of_cylinder = v)
#define fdt_image_config_setsectorsize(config, v) (config->sector_size = v)
#define fdt_image_config_setrpm(config, v) (config->rpm = v)
#define fdt_image_config_setwriteprotect(config, v) (config->write_protect = v)

#define fdt_image_config_hasname(config) ((0 < fdt_string_length(config->name)) ? true : false)
#define fdt_image_config_getname(config) fdt_string_getvalue(config->name)
#define fdt_image_config_getsize(config) (config->size)
#define fdt_image_config_getdensity(config) (config->density)
#define fdt_image_config_getdensitystring(config) fdt_image_density_getstring(config->density)
#define fdt_image_config_getnumberofhead(config) (config->number_of_head)
#define fdt_image_config_getnumberofsector(config) (config->number_of_sector)
#define fdt_image_config_getnumberofcylinder(config) (config->number_of_cylinder)
#define fdt_image_config_getsectorsize(config) (config->sector_size)
#define fdt_image_config_getrpm(config) (config->rpm)
#define fdt_image_config_getwriteprotect(config) (config->write_protect)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_CONFIG_H_ */
