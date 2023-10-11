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

#ifndef _FDTOOLS_FMT_X68_H_
#define _FDTOOLS_FMT_X68_H_

#include <fdtools/fmt/format.h>
#include <fdtools/img/image.h>
#include <fdtools/plugins/fmt/dos/bpb.h>

#ifdef __cplusplus
extern "C" {
#endif

const size_t FDT_X68_FD_CYLINDER = 77;
const size_t FDT_X68_FD_HEAD = 2;
const size_t FDT_X68_FD_SECTOR = 8;
const size_t FDT_X68_FD_SECTOR_SIZE = 1024;

FdtImage* fdt_x68_floppy_image_new(void);
FdtImage* fdt_x68_floppy_from(const char*, FdtError*);
bool fdt_x68_image_generate(FdtImage*);
bool fdt_x68_image_delete(FdtImage*);
bool fdt_x68_image_isfloppy(FdtImage*);

FdtFormat* fdt_x68_format_new(void);
const char* fdt_x68_format_gettypeid(FdtFormat* fmt);
bool fdt_x68_format_format(FdtFormat* fmt);
bool fdt_x68_format_list(FdtFormat* fmt, FdtFiles* files);
bool fdt_x68_format_add(FdtFormat* fmt, FdtFile* file);
bool fdt_x68_format_del(FdtFormat* fmt, FdtFile* file);

bool fdt_x68_format_loadimage(FdtImage*, FdtError*);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_FMT_X68_H_ */