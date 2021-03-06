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

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include <fdtools/img/file.h>
#include <fdtools/img/hfe.h>
#include <fdtools/util/array.h>

#include "image_test.h"

BOOST_AUTO_TEST_CASE(HfeHeaderSizeTest)
{
  BOOST_CHECK_EQUAL(sizeof(FdtHfeHeader), HFE_HEADER_SIZE);
}

BOOST_AUTO_TEST_CASE(HfeImageLoaderTest)
{
  const char TEST_HFE_IMAGES[][64] = {
    "test-001.hfe",
    "test-002.hfe",
    "test-003.hfe",
  };

  FdtError* err = fdt_error_new();

  for (int n = 0; n < fdt_array_countof(TEST_HFE_IMAGES); n++) {
    std::string filename = TEST_IMAGE_DIRECTORY + "/" + TEST_HFE_IMAGES[n];
    boost::filesystem::path filepath(filename);
    if (!boost::filesystem::exists(filepath))
      continue;

    BOOST_CHECK_EQUAL(fdt_image_name_gettype(filename.c_str()), FDT_IMAGE_TYPE_HFE);

    FdtImage* img = fdt_hfe_image_new();
    BOOST_CHECK(img);
    BOOST_CHECK(fdt_image_open(img, filename.c_str(), FDT_FILE_READ, err));
    BOOST_CHECK(fdt_image_load(img, err));
    //fdt_image_print(img);
    BOOST_CHECK(fdt_image_close(img, err));
    fdt_image_delete(img);
  }

  fdt_error_delete(err);
}
