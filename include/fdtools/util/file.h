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

#ifndef _FDTOOLS_UTIL_FILE_H_
#define _FDTOOLS_UTIL_FILE_H_

#include <stdlib.h>

#include <fdtools/typedef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  FDT_FILE_READ = 0x01,
  FDT_FILE_WRITE = 0x20,
} FdtFileMode;

FILE* fdt_file_open(const char*, FdtFileMode);
bool fdt_file_close(FILE*);

FILE* fdt_file_memopen(byte* buf, size_t n, FdtFileMode mode);
bool fdt_file_memclose(FILE*);

bool fdt_file_read(FILE*, void*, size_t);
bool fdt_file_write(FILE*, void*, size_t);
bool fdt_file_seek(FILE*, long, int);

bool fdt_file_hasextension(const char* filename, const char* extname);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_FILE_H_ */
