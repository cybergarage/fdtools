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

#include <fdtools/typedef.h>
#include <fdtools/util/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  FDT_DENSITY_UNKNOWN = 0,
  FDT_DENSITY_SD = 1,
  FDT_DENSITY_DD = 2,
  FDT_DENSITY_HD = 3,
  FDT_DENSITY_QD = 4,
  FDT_DENSITY_ED = 5,
} FdtDensity;

typedef struct {
  FdtString* name;
  FdtDensity density_type;
  int rpm;
  int number_of_head;
  int number_of_sector;
  int number_of_cylinder;
  int sector_size;
} FdtImageConfig;

FdtImageConfig* fdt_image_config_new();
void fdt_image_config_delete(FdtImageConfig*);
void fdt_image_config_print(FdtImageConfig*);

#define fdt_image_config_setname(config, v) fdt_string_setvalue(config->name, v)
#define fdt_image_config_setdensitytype(config, n) (config->density_type = n)
#define fdt_image_config_setrpm(config, n) (config->rpm = n)
#define fdt_image_config_setnumberofhead(config, n) (config->number_of_head = n)
#define fdt_image_config_setnumberofsector(config, n) (config->number_of_sector = n)
#define fdt_image_config_setnumberofcylinder(config, n) (config->number_of_cylinder = n)
#define fdt_image_config_setsectorsize(config, n) (config->sector_size = n)

#define fdt_image_config_getname(config) fdt_string_getvalue(config->name)
#define fdt_image_config_getdensitytype(config) (config->density_type)
#define fdt_image_config_getrpm(config) (config->rpm)
#define fdt_image_config_getnumberofhead(config) (config->number_of_head)
#define fdt_image_config_getnumberofsector(config) (config->number_of_sector)
#define fdt_image_config_getnumberofcylinder(config) (config->number_of_cylinder)
#define fdt_image_config_getsectorsize(config) (config->sector_size)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_CONFIG_H_ */
