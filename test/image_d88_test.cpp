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

#include <fdtools/img/d88.h>
#include <fdtools/util/array.h>

#include "image_test.h"

BOOST_AUTO_TEST_CASE(D88HeaderSizeTest)
{
  BOOST_CHECK_EQUAL(sizeof(FdtD88Header), D88_HEADER_SIZE);
}

BOOST_AUTO_TEST_CASE(D88ImageLoaderTest)
{
  const char TEST_D88_IMAGES[][64] = {
    "test-001.d88",
    "test-002.d88",
    "test-003.d88",
    "test-004.d88",
  };

  FdtError* err = fdt_error_new();
  for (int n = 0; n < fdt_array_countof(TEST_D88_IMAGES); n++) {
    std::string filename = TEST_IMAGE_DIRECTORY + "/" + TEST_D88_IMAGES[n];
    boost::filesystem::path filepath(filename);
    if (!boost::filesystem::exists(filepath))
      continue;

    BOOST_CHECK_EQUAL(fdt_image_name_gettype(filename.c_str()), FDT_IMAGE_TYPE_D88);

    ImageLorderComareTest(filepath, fdt_d88_image_new, fdt_d88_image_new, err);
  }
  fdt_error_delete(err);
}
