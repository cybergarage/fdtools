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

#ifndef _FDTOOLS_IMG_HEADER_H_
#define _FDTOOLS_IMG_HEADER_H_

#include <fdtools/img/config.h>
#include <fdtools/typedef.h>

#ifdef __cplusplus
extern "C" {
#endif

const int FDT_IMAGE_HEADER_SIGNATURE_MAX = 8;

typedef enum {
  FDT_IMAGE_TYPE_UNKNOWN,
  FDT_IMAGE_TYPE_RAW,
  FDT_IMAGE_TYPE_HFE,
  FDT_IMAGE_TYPE_D88,
} FdtImageType;

typedef struct {
  FDT_IMAGE_CONFIG_MEMBERS
} FdtImageHeader;

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_FILE_H_ */
