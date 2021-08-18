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

#ifndef _FDTOOLS_IMG_ERROR_H_
#define _FDTOOLS_IMG_ERROR_H_

#include <fdtools/error.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FDT_IMAGE_MESSAGE_SECTOR_PRINTF_FORMAT "C:%02ld H:%01ld R:%02ld"
#define FDT_IMAGE_MESSAGE_SECTOR_SIZE_PRINTF_FORMAT FDT_IMAGE_MESSAGE_SECTOR_PRINTF_FORMAT " SIZE:%ld"
#define FDT_IMAGE_MESSAGE_UNKNOWN_TYPE_FORMAT "Unknown image type: %s"
#define FDT_IMAGE_MESSAGE_SECTORS_NOT_SORTED "Sectors aren't sorted: %s"
#define FDT_IMAGE_MESSAGE_UNKNOWN_DENSITY_FORMAT "Unknown density: %s"
#define FDT_IMAGE_MESSAGE_LOADER_NOT_SUPPORTED "%s : Loader is not supported"

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_ERROR_H_ */
