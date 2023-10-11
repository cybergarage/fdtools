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

BOOST_AUTO_TEST_CASE(FormatX68Test)
{
  FdtImage* img = fdt_x68_image_new();
  BOOST_CHECK(img);
  BOOST_CHECK_EQUAL(fdt_image_getnumberofcylinder(img), FDT_X68_FD_CYLINDER);
  BOOST_CHECK_EQUAL(fdt_image_getnumberofhead(img), FDT_X68_FD_HEAD);
  BOOST_CHECK_EQUAL(fdt_image_getnumberofsector(img), FDT_X68_FD_SECTOR);
  BOOST_CHECK_EQUAL(fdt_image_getsectorsize(img), FDT_X68_FD_SECTOR_SIZE);
  BOOST_CHECK(fdt_x68_image_generate(img));
  BOOST_CHECK(fdt_x68_image_delete(img));
}
