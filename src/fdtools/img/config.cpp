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

#include <fdtools/img/config.h>

FdtImageConfig* fdt_image_config_new()
{
  FdtImageConfig* config;

  config = (FdtImageConfig*)malloc(sizeof(FdtImageConfig));
  if (!config) {
    return NULL;
  }

  config->name = fdt_string_new();

  fdt_image_config_setname(config, "");
  fdt_image_config_setsize(config, 0);
  fdt_image_config_setdensitytype(config, FDT_DENSITY_UNKNOWN);
  fdt_image_config_setnumberofhead(config, 0);
  fdt_image_config_setnumberofsector(config, 0);
  fdt_image_config_setnumberofcylinder(config, 0);
  fdt_image_config_setsectorsize(config, 0);
  fdt_image_config_setwriteprotect(config, false);

  return config;
}

void fdt_image_config_delete(FdtImageConfig* config)
{
  if (!config)
    return;

  fdt_string_delete(config->name);
  free(config);
}

void fdt_image_config_print(FdtImageConfig* config)
{
  printf("name               : %s\n", fdt_image_config_getname(config));
  printf("size               : %ld\n", fdt_image_config_getsize(config));
  printf("density            : %d\n", config->density_type);
  printf("number_of_cylinder : %ld\n", config->number_of_cylinder);
  printf("number_of_head     : %ld\n", config->number_of_head);
  printf("number_of_sector   : %ld\n", config->number_of_sector);
  printf("sector_size        : %ld\n", config->sector_size);
  printf("rpm                : %d\n", config->rpm);
  printf("write_protect      : %d\n", config->write_protect);
}
