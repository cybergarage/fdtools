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

#ifndef _FDTOOLS_UTIL_STRUCT_H_
#define _FDTOOLS_UTIL_STRUCT_H_

#include <fdtools/typedef.h>

#ifdef __cplusplus
extern "C" {
#endif

bool fdt_structcmp(void* t, void* o, off_t offset, size_t size)
{
  if (!t || !o)
    return false;
  return (memcmp((((byte_t*)t) + offset), (((byte_t*)o) + offset), size) == 0) ? true : false;
}

bool fdt_structcpy(void* dest, void* src, off_t offset, size_t size)
{
  if (!dest || !src)
    return false;
  memcpy((((byte_t*)dest) + offset), (((byte_t*)src) + offset), size);
  return true;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _FDTOOLS_UTIL_STRUCT_H_ */
