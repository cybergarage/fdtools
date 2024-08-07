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

#ifndef _FDTOOLS_UTIL_BYTES_H_
#define _FDTOOLS_UTIL_BYTES_H_

#include <fdtools/typedef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

byte_t fdt_byte_fromlebytes(byte_t bytes[1]);
void fdt_byte_setbytes(byte_t v, byte_t bytes[1]);

unsigned short fdt_ushort_fromlebytes(byte_t bytes[2]);
void fdt_ushort_setlebytes(unsigned short v, byte_t bytes[2]);

unsigned short fdt_uint_fromlebytes(byte_t bytes[4]);
void fdt_uint_setlebytes(unsigned short v, byte_t bytes[4]);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_UTIL_BYTES_H_ */
