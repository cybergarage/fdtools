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

#ifndef _FDTOOLS_IMG_FILE_H_
#define _FDTOOLS_IMG_FILE_H_

#include <stdio.h>
#include <stdlib.h>

#include <fdtools/img/error.h>
#include <fdtools/img/image.h>
#include <fdtools/util/file.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FDT_ATTR_PACKED {
  FDT_IMAGE_STRUCT_MEMBERS
  FILE* fp;
} FdtFileImage;

FdtImage* fdt_image_file_new(void);

inline bool fdt_image_file_isvalid(FdtFileImage* img, FdtError* err) { return fdt_image_isvalid(((FdtImage*)img), err); }
inline void fdt_image_file_setfile(FdtFileImage* img, FILE* v) { ((FdtFileImage*)img)->fp = v; }
inline FILE* fdt_image_file_getfile(FdtFileImage* img) { return img->fp; }

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_FILE_H_ */
