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

#include "image_test.h"
#include <fdtools/plugins/image.h>

BOOST_AUTO_TEST_CASE(ImagePluginTest)
{
  FdtError* err = fdt_error_new();

  boost::filesystem::path test_img_path(TEST_IMAGE_DIRECTORY);
  boost::filesystem::recursive_directory_iterator end;
  for (boost::filesystem::recursive_directory_iterator it(test_img_path); it != end; ++it) {
    const boost::filesystem::path test_img_file = (*it);
    if (!boost::filesystem::exists(test_img_file))
      continue;
    FdtImage* test_img = fdt_image_plugins_create(test_img_file.c_str(), err);
    if (!test_img)
      continue;
    BOOST_TEST_MESSAGE(test_img_file);
    BOOST_CHECK(fdt_image_delete(test_img));
  }
}
