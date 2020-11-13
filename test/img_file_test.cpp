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

const char* TEST_IMAGE_DIRECTORY = "./img";

BOOST_AUTO_TEST_CASE(HfeImageTest)
{
  const char* TEST_HFE_IMAGES[][64] = {
    "cpm-x1-v220-blank.hfe"
  };

  for (int n = 0; n < fdt_array_countof(TEST_HFE_IMAGES); n++) {
    fdt_img_file_gettype(*TEST_HFE_IMAGES[n]);
  }
}
