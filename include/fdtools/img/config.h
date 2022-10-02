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

#include <fdtools/img/density.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FDT_ATTR_PACKED {
  FdtString* name;
  FdtString* desc;
  FdtImageDensity density;
  size_t size;
  size_t number_of_head;
  size_t number_of_sector;
  size_t number_of_cylinder;
  size_t sector_size;
  int bitrate;
  int rpm;
  bool write_protect;
} FdtImageConfig;

FdtImageConfig* fdt_image_config_new();
bool fdt_image_config_delete(FdtImageConfig*);

bool fdt_image_config_isvalid(FdtImageConfig*, FdtError*);
FdtImageConfig* fdt_image_config_copy(FdtImageConfig*);
bool fdt_image_config_equals(FdtImageConfig*, FdtImageConfig*, FdtError*);

bool fdt_image_config_autoparametersbysize(FdtImageConfig*, size_t);
FdtImageDensity fdt_image_config_getsupposeddensity(FdtImageConfig*);
size_t fdt_image_config_calculaterawsize(FdtImageConfig*);
const char* fdt_image_config_getdescription(FdtImageConfig*);
void fdt_image_config_print(FdtImageConfig*);

inline void fdt_image_config_setname(FdtImageConfig* config, const char* v) { fdt_string_setvalue(config->name, v); }
inline void fdt_image_config_setsize(FdtImageConfig* config, size_t v) { config->size = v; }
inline void fdt_image_config_setdensity(FdtImageConfig* config, FdtImageDensity v) { config->density = v; }
inline void fdt_image_config_setnumberofhead(FdtImageConfig* config, size_t v) { config->number_of_head = v; }
inline void fdt_image_config_setnumberofsector(FdtImageConfig* config, size_t v) { config->number_of_sector = v; }
inline void fdt_image_config_setnumberofcylinder(FdtImageConfig* config, size_t v) { config->number_of_cylinder = v; }
inline void fdt_image_config_setsectorsize(FdtImageConfig* config, size_t v) { config->sector_size = v; }
inline void fdt_image_config_setbitrate(FdtImageConfig* config, int v) { config->bitrate = v; }
inline void fdt_image_config_setrpm(FdtImageConfig* config, int v) { config->rpm = v; }
inline void fdt_image_config_setwriteprotectenabled(FdtImageConfig* config, bool v) { config->write_protect = v; }

inline bool fdt_image_config_hasname(FdtImageConfig* config) { return ((0 < fdt_string_length(config->name)) ? true : false); }
inline const char* fdt_image_config_getname(FdtImageConfig* config) { return fdt_string_getvalue(config->name); }
inline size_t fdt_image_config_getsize(FdtImageConfig* config) { return config->size; }
inline FdtImageDensity fdt_image_config_getdensity(FdtImageConfig* config) { return config->density; }
inline const char* fdt_image_config_getdensitystring(FdtImageConfig* config) { return fdt_image_density_getstring(config->density); }
inline size_t fdt_image_config_getnumberofhead(FdtImageConfig* config) { return config->number_of_head; }
inline size_t fdt_image_config_getnumberofsector(FdtImageConfig* config) { return config->number_of_sector; }
inline size_t fdt_image_config_getnumberofcylinder(FdtImageConfig* config) { return config->number_of_cylinder; }
inline size_t fdt_image_config_getsectorsize(FdtImageConfig* config) { return config->sector_size; }
inline int fdt_image_config_getbitrate(FdtImageConfig* config) { return config->bitrate; }
inline int fdt_image_config_getrpm(FdtImageConfig* config) { return config->rpm; }
inline bool fdt_image_config_iswriteprotectenabled(FdtImageConfig* config) { return config->write_protect; }

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_CONFIG_H_ */
