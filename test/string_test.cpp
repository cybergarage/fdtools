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
#include <fdtools/util/string.h>

BOOST_AUTO_TEST_CASE(StringAddValue)
{
  const char TEST_STRINGS[] = "abcdefghijklmnopqrstuvwxyz";

  FdtString* str = fdt_string_new();
  BOOST_REQUIRE(str);

  char ch[2] = { 0x00, 0x00 };
  for (int n = 0; n < fdt_array_countof(TEST_STRINGS); n++) {
    ch[0] = TEST_STRINGS[n];
    BOOST_CHECK(fdt_string_appendvalue(str, ch));
  }

  BOOST_CHECK_EQUAL(fdt_string_getvalue(str), TEST_STRINGS);
  BOOST_CHECK_EQUAL(fdt_string_length(str), fdt_array_countof(TEST_STRINGS) - 1);

  BOOST_CHECK(fdt_string_delete(str));
}
