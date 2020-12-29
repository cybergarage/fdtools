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

#include <fdtools/util/dictionary.h>

BOOST_AUTO_TEST_CASE(DictionaryTest)
{
  const int TEST_DICTIONARY_ELEMENT_COUNT = 10;

  char key[8], value[8];

  FdtDictionary* dir = fdt_dictionary_new();
  BOOST_REQUIRE(dir);

  for (int i = 0; i < 2; i++) {
    for (int n = 0; n < TEST_DICTIONARY_ELEMENT_COUNT; n++) {
      snprintf(key, sizeof(key), "%d", n);
      snprintf(value, sizeof(value), "%d", n);
      BOOST_CHECK(fdt_dictionary_setstring(dir, key, value));
      BOOST_CHECK_EQUAL(value, fdt_dictionary_getstring(dir, key));
    }
    BOOST_CHECK_EQUAL(fdt_dictionary_size(dir), TEST_DICTIONARY_ELEMENT_COUNT);
  }

  BOOST_CHECK(fdt_dictionary_delete(dir));
}
