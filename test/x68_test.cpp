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

BOOST_AUTO_TEST_CASE(X68FormatTest)
{
  FdtError* err = fdt_error_new();

  FdtImage* img = fdt_x68_floppy_image_new();
  BOOST_REQUIRE(img);
  BOOST_REQUIRE(fdt_x68_image_isfloppy(img));
  BOOST_REQUIRE(fdt_x68_image_generate(img));
  BOOST_REQUIRE(fdt_x68_image_isfloppy(img));

  //  FdtFormat* fmt = fdt_x68_from(img);
  //  BOOST_REQUIRE(img);
  //  BOOST_REQUIRE_MESSAGE(fdt_format_format(fmt, err), fdt_error_getmessage(err));
  //  BOOST_CHECK(fdt_format_delete(fmt));

  FdtImage* org_img = fdt_x68_floppy_image_from(TEST_X86_BLANK_IMAGE.c_str(), err);
  BOOST_REQUIRE_MESSAGE(org_img, fdt_error_getmessage(err));

  BOOST_REQUIRE_MESSAGE(fdt_image_equals(img, org_img, err), fdt_error_getmessage(err));

  BOOST_CHECK(fdt_error_delete(err));
  BOOST_CHECK(fdt_x68_image_delete(img));
  BOOST_CHECK(fdt_x68_image_delete(org_img));
}
