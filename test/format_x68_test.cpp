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
#include <fdtools/plugins/fmt/x68/x68.h>

const std::string TEST_X86_BLANK_IMAGE = "./img/525-2hd-x68.xdf";

BOOST_AUTO_TEST_CASE(FormatX68Test)
{
  FdtError* err = fdt_error_new();

  FdtImage* img = fdt_x68_floppy_image_new();
  BOOST_CHECK(img);
  BOOST_CHECK(fdt_x68_image_isfloppy(img));
  BOOST_CHECK(fdt_x68_image_generate(img));
  BOOST_CHECK(fdt_x68_image_isfloppy(img));
  BOOST_CHECK(fdt_x68_image_delete(img));

   FdtImage* org_img = fdt_x68_floppy_image_from(TEST_X86_BLANK_IMAGE.c_str(), err);
  BOOST_CHECK(org_img);
  BOOST_CHECK(fdt_x68_image_delete(org_img));

  fdt_error_delete(err);
}
