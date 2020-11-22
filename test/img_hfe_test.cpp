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
#include <fdtools/img/file.h>
#include <fdtools/util/array.h>

const std::string TEST_IMAGE_DIRECTORY = "./img";

BOOST_AUTO_TEST_CASE(HfeHeaderSizeTest)
{
  BOOST_CHECK_EQUAL(sizeof(FdtHfeRawHeader), HFE_HEADER_SIZE);
}

BOOST_AUTO_TEST_CASE(HfeImageLoadTest)
{
  const char* TEST_HFE_IMAGES[][64] = {
    //"test-001.hfe",
    //"test-002.hfe",
    //"test-003.hfe",
  };

  for (int n = 0; n < fdt_array_countof(TEST_HFE_IMAGES); n++) {
    std::string filename = TEST_IMAGE_DIRECTORY + "/" + *TEST_HFE_IMAGES[n];
    BOOST_CHECK_EQUAL(fdt_img_file_gettype(filename.c_str()), FDT_IMAGE_TYPE_HFE);

    FILE* fp = fdt_file_open(filename.c_str());
    BOOST_CHECK(fp);
    if (!fp)
      continue;

    FdtHfeHeader* header = fdt_hfe_header_new();
    BOOST_CHECK(fdt_hfe_header_load(header, fp));
    fdt_hfe_header_delete(header);

    fdt_file_close(fp);
  }
}
