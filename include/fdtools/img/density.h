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

#ifndef _FDTOOLS_IMG_DENSITY_H_
#define _FDTOOLS_IMG_DENSITY_H_

#include <stdlib.h>

#include <fdtools/typedef.h>

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

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_DENSITY_H_ */
