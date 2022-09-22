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

#ifndef _FDTOOLS_IMG_RAW_H_
#define _FDTOOLS_IMG_RAW_H_

#include <fdtools/img/file.h>

#ifdef __cplusplus
extern "C" {
#endif

const char FDT_RAW_EXTENTION_RAW[] = "raw";
const char FDT_RAW_EXTENTION_IMG[] = "img";

FdtImage* fdt_raw_image_new(void);

const char* fdt_raw_image_gettypeid(FdtImage* img);
bool fdt_raw_image_getextentions(FdtImage* img, FdtStrings* strs);
bool fdt_raw_image_load(FdtFileImage*, FdtError* err);
bool fdt_raw_image_export(FdtFileImage*, FdtError* err);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_RAW_H_ */
