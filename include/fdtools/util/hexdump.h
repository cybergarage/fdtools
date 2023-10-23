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

#ifndef _FDTOOLS_UTIL_HEXDUMP_H_
#define _FDTOOLS_UTIL_HEXDUMP_H_

#include <fdtools/typedef.h>

#ifdef __cplusplus
extern "C" {
#endif

const size_t FDT_HEXDUMP_LINE_BYTES = 16;

void fdt_hexdump_print(byte_t* buf, size_t buf_len);
void fdt_hexdump_line_print(byte_t* buf, size_t offset, size_t line_len);

void fdt_hexdump_compare_print(byte_t* buf_l, size_t buf_l_len, byte_t* buf_r, size_t buf_r_len);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _FDTOOLS_UTIL_HEXDUMP_H_ */
