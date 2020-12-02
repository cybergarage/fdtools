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

#include <boost/test/unit_test.hpp>

#include <fdtools/util/array.h>
#include <fdtools/util/logic.h>

BOOST_AUTO_TEST_CASE(BitSwapTest)
{
  byte_t b[5] = { 0x00, 0x01, 0x02, 0x04, 0x80 };
  byte_t rb[5] = { 0x00, 0x80, 0x40, 0xC0, 0x20 };

  for (int n = 0; n < fdt_array_countof(b); n++) {
    BOOST_CHECK_EQUAL(fdt_swapbyte(b[n]), rb[n]);
  }
}
