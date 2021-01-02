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
#include <fdtools/img/raw.h>
#include <fdtools/util/array.h>

#include "image_test.h"

FdtImage* fdt_raw_pc_image_new(void)
{
  FdtImage* img = fdt_raw_image_new();
  fdt_image_setnumberofcylinder(img, 80);
  fdt_image_setnumberofhead(img, 2);
  fdt_image_setnumberofsector(img, 18);
  fdt_image_setsectorsize(img, 512);
  return img;
}

BOOST_AUTO_TEST_CASE(RAWImageLoaderTest)
{
  const char TEST_RAW_IMAGES[][64] = {
    "test-001.img",
  };

  for (int n = 0; n < fdt_array_countof(TEST_RAW_IMAGES); n++) {
    std::string filename = TEST_IMAGE_DIRECTORY + "/" + TEST_RAW_IMAGES[n];
    boost::filesystem::path filepath(filename);
    if (!boost::filesystem::exists(filepath))
      continue;

    BOOST_CHECK_EQUAL(fdt_image_name_gettype(filename.c_str()), FDT_IMAGE_TYPE_RAW);

    ImageLoarderExporterCompareTest(filepath, fdt_raw_pc_image_new);
  }
}
