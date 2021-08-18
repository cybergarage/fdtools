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

#ifndef _FDTOOLS_UTIL_LOGIC_H_
#define _FDTOOLS_UTIL_LOGIC_H_

#include <fdtools/typedef.h>

#ifdef __cplusplus
extern "C" {
#endif

inline byte_t fdt_swapbyte(byte_t x)
{
  x = ((x & 0xF0) >> 4 | ((x & 0x0F) << 4) & 0x0F);
  x = ((x & 0xCC) >> 2 | ((x & 0x33) << 2) & 0x33);
  x = ((x & 0xAA) >> 1 | ((x & 0x55) << 1) & 0x55);
  return x;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _FDTOOLS_UTIL_LOGIC_H_ */
