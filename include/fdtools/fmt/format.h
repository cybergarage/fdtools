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

#ifndef _FDTOOLS_FMT_FORMAT_H_
#define _FDTOOLS_FMT_FORMAT_H_

#include <stdio.h>

#include <fdtools/error.h>
#include <fdtools/typedef.h>
#include <fdtools/util/file.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  FDT_FORMAT_TYPE_UNKNOWN,
  FDT_FORMAT_TYPE_DOS,
  FDT_FORMAT_TYPE_CPM,
} FdtFormatType;

typedef FdtFormatType (*FDT_FORMAT_GETTYPE)(void*);
typedef const char* (*FDT_FORMAT_GETTYPEID)(void*);
typedef bool (*FDT_FORMAT_DESTRUCTOR)(void*);

#define FDT_FORMAT_STRUCT_MEMBERS       \
  FdtFormatType type;     \
  FDT_FORMAT_GETTYPEID image_gettypeid; \
  FDT_FORMAT_DESTRUCTOR image_destructor;

typedef struct FDT_ATTR_PACKED {
  FDT_FORMAT_STRUCT_MEMBERS
} FdtFormat;

typedef FdtFormat* (*FDT_FORMAT_FORMATTER)(void);

FdtFormat* fdt_format_new();
bool fdt_format_delete(FdtFormat*);
bool fdt_format_init(FdtFormat*);

FdtFormatType fdt_format_gettype(FdtFormat*);
const char* fdt_image_gettypeid(FdtFormat*);

#define fdt_format_setgettypeid(img, fn) (img->image_gettypeid = (FDT_FORMAT_GETTYPEID)fn)
#define fdt_format_setdestructor(img, fn) (img->image_destructor = (FDT_FORMAT_DESTRUCTOR)fn)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_IMAGE_H_ */
