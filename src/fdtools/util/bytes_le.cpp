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

#include <fdtools/util/bytes.h>

unsigned short fdt_ushort_fromlebytes(byte_t bytes[2])
{
  return (bytes[0] << 0) | (bytes[1] << 8);
}

void fdt_ushort_setlebytes(unsigned short v, byte_t bytes[2])
{
  bytes[0] = (v >> 0) & 0xff;
  bytes[1] = (v >> 8) & 0xff;
}

unsigned short fdt_uint_fromlebytes(byte_t bytes[4])
{
  return (bytes[0] << 0) | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
}

void fdt_uint_setlebytes(unsigned short v, byte_t bytes[4])
{
  bytes[0] = (v >> 0) & 0xff;
  bytes[1] = (v >> 8) & 0xff;
  bytes[2] = (v >> 16) & 0xff;
  bytes[3] = (v >> 24) & 0xff;
}
