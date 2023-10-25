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

#include <fdtools/util/bytes.h>

BOOST_AUTO_TEST_CASE(LittleEndianUshortBytes)
{
  byte_t bytes[2];
  unsigned short value = 0x1234;
  fdt_ushort_setlebytes(value, bytes);
  BOOST_CHECK_EQUAL(bytes[0], 0x34);
  BOOST_CHECK_EQUAL(bytes[1], 0x12);
  BOOST_CHECK_EQUAL(fdt_ushort_fromlebytes(bytes), value);
}

BOOST_AUTO_TEST_CASE(LittleEndianUintBytes)
{
  byte_t bytes[4];
  unsigned int value = 0x12345678;
  fdt_uint_setlebytes(value, bytes);
  BOOST_CHECK_EQUAL(bytes[0], 0x78);
  BOOST_CHECK_EQUAL(bytes[1], 0x56);
  BOOST_CHECK_EQUAL(bytes[2], 0x34);
  BOOST_CHECK_EQUAL(bytes[3], 0x12);
  BOOST_CHECK_EQUAL(fdt_uint_fromlebytes(bytes), value);
}
