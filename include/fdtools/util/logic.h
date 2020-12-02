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
  byte_t r = 0;
  for (int n = 0; n < 8; n++) {
    r <<= 1;
    r &= 0xFF;
    r |= (x & 0x01);
    x >>= 1;
  }
  return (r & 0xFF);
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _FDTOOLS_UTIL_LIST_H_ */
