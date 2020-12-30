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

#include <fdtools/img/config.h>
#include <fdtools/util/struct.h>

FdtImageConfig* fdt_image_config_new()
{
  FdtImageConfig* config = (FdtImageConfig*)calloc(sizeof(FdtImageConfig), 1);
  if (!config) {
    return NULL;
  }

  config->name = fdt_string_new();
  config->desc = fdt_string_new();
  if (!config->name || !config->desc) {
    fdt_image_config_delete(config);
    return NULL;
  }

  fdt_image_config_setname(config, "");
  fdt_image_config_setsize(config, 0);
  fdt_image_config_setdensity(config, FDT_DENSITY_UNKNOWN);
  fdt_image_config_setnumberofhead(config, 0);
  fdt_image_config_setnumberofsector(config, 0);
  fdt_image_config_setnumberofcylinder(config, 0);
  fdt_image_config_setsectorsize(config, 0);
  fdt_image_config_setrpm(config, 0);
  fdt_image_config_setwriteprotect(config, false);

  return config;
}

bool fdt_image_config_delete(FdtImageConfig* config)
{
  if (!config)
    return false;

  if (config->name) {
    fdt_string_delete(config->name);
  }
  if (config->desc) {
    fdt_string_delete(config->desc);
  }

  free(config);
  return true;
}

const char* fdt_image_config_getdensitystring(FdtImageConfig* config)
{
  switch (config->density) {
  case FDT_DENSITY_SD:
    return "SD";
  case FDT_DENSITY_DD:
    return "DD";
  case FDT_DENSITY_HD:
    return "HD";
  case FDT_DENSITY_QD:
    return "QD";
  case FDT_DENSITY_ED:
    return "ED";
  case FDT_DENSITY_UNKNOWN:
    return "";
  }
  return "";
}

bool fdt_image_config_isvalid(FdtImageConfig* config, FdtError* err)
{
  if (!config)
    return false;

  if (fdt_image_config_getnumberofhead(config) <= 0 || fdt_image_config_getnumberofsector(config) <= 0 || fdt_image_config_getnumberofcylinder(config) <= 0 || fdt_image_config_getsectorsize(config) <= 0) {
    fdt_error_setmessage(err, "Invalid Parameters cylinder:%ld, head:%ld, sector:%ld, ssize:%ld", fdt_image_config_getnumberofcylinder(config), fdt_image_config_getnumberofhead(config), fdt_image_config_getnumberofsector(config), fdt_image_config_getsectorsize(config));
    return false;
  }

  return true;
}

bool fdt_image_config_equals(FdtImageConfig* config, FdtImageConfig* other, FdtError* err)
{
  if (!fdt_string_equals(config->name, other->name)) {
    fdt_error_setmessage(err, "%s != %s", fdt_string_getvalue(config->name), fdt_string_getvalue(other->name));
    return false;
  }

  off_t config_offset = sizeof(FdtString*) /* name */ + sizeof(FdtString*) /* desc */;
  size_t config_comp_size = sizeof(FdtImageConfig) - config_offset;
  if (!fdt_structcmp(config, other, config_offset, config_comp_size)) {
    fdt_error_setmessage(err, "%s != %s", fdt_image_config_getdescription(config), fdt_image_config_getdescription(other));
    return false;
  }

  return true;
}

size_t fdt_image_config_calculaterawsize(FdtImageConfig* config)
{
  if (!config)
    return 0;
  return config->number_of_cylinder * config->number_of_head * config->number_of_sector * config->sector_size;
}

const char* fdt_image_config_getdescription(FdtImageConfig* config)
{
  fdt_string_setvaluef(config->desc, "cylinder:%ld, head:%ld, sector:%ld, ssize:%ld", config->number_of_cylinder, config->number_of_head, config->number_of_sector, config->sector_size);
  return fdt_string_getvalue(config->desc);
}

void fdt_image_config_print(FdtImageConfig* config)
{
  printf("name               : %s\n", fdt_image_config_getname(config));
  printf("size               : %ld\n", fdt_image_config_getsize(config));
  printf("density            : %s\n", fdt_image_config_getdensitystring(config));
  printf("number of cylinder : %ld\n", config->number_of_cylinder);
  printf("number of head     : %ld\n", config->number_of_head);
  printf("number of sector   : %ld\n", config->number_of_sector);
  printf("sector size        : %ld\n", config->sector_size);
  printf("rpm                : %d\n", config->rpm);
  printf("write_protect      : %d\n", config->write_protect);
}
