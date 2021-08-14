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
  BOOST_REQUIRE(err);

  boost::filesystem::path test_img_path(TEST_IMAGE_DIRECTORY);
  boost::filesystem::recursive_directory_iterator end;
  for (boost::filesystem::recursive_directory_iterator it(test_img_path); it != end; ++it) {
    const boost::filesystem::path test_img_filepath = (*it);
    if (!boost::filesystem::exists(test_img_filepath))
      continue;

    const boost::filesystem::path test_img_filename = test_img_filepath.filename();

    FDT_IMAGE_IMAGER test_imager = fdt_image_plugins_getimager(test_img_filepath.c_str(), err);
    if (!test_imager)
      continue;

    // Loads a found test disk image

    BOOST_TEST_MESSAGE("Loading   " << test_img_filename);

    FdtImage* test_img = test_imager();
    BOOST_REQUIRE(test_img);
    fdt_image_settarget(test_img, test_img_filepath.c_str());
    fdt_image_setname(test_img, test_img_filename.c_str());
    BOOST_REQUIRE_MESSAGE(fdt_image_load(test_img, err), fdt_error_getdebugmessage(err));

    BOOST_TEST_MESSAGE("Loaded    " << fdt_image_getname(test_img) << " (" << fdt_image_gettypeid(test_img) << ")");

    // Exports the loaded image to a memory file

    ImageLoarderExporterCompareTest(test_img, test_imager);

    BOOST_CHECK(fdt_image_delete(test_img));
  }

  BOOST_CHECK(fdt_error_delete(err));
}
