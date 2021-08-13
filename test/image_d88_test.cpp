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

#include <fdtools/plugins/d88/d88.h>
#include <fdtools/plugins/plugin.h>
#include <fdtools/util/array.h>

#include "image_test.h"

BOOST_AUTO_TEST_CASE(D88HeaderSizeTest)
{
  BOOST_CHECK_EQUAL(sizeof(FdtD88Header), D88_HEADER_SIZE);
}

void TEST_CHECK_D88_DISKTYPE_EQUAL(FdtImage* img, int c, int h, int s, int ssize, uint8_t d88_disk_type)
{

  fdt_image_setnumberofcylinder(img, c);
  fdt_image_setnumberofhead(img, h);
  fdt_image_setnumberofsector(img, s);
  fdt_image_setsectorsize(img, ssize);

  FdtD88Header d88_header;
  fdt_d88_header_setconfig(&d88_header, img, NULL);

  char msg[256];
  snprintf(msg, sizeof(msg), "(%d, %d, %d, %d) != %d", c, h, s, ssize, d88_disk_type);
  BOOST_CHECK_MESSAGE((d88_header.disk_type == d88_disk_type), msg);
}

BOOST_AUTO_TEST_CASE(D88ConfigTest)
{
  FdtImage* img = fdt_image_new();
  BOOST_REQUIRE(img);

  TEST_CHECK_D88_DISKTYPE_EQUAL(img, 40, 2, 16, 256, D88_DISK_TYPE_2DD);
  TEST_CHECK_D88_DISKTYPE_EQUAL(img, 77, 2, 16, 256, D88_DISK_TYPE_2HD);
  TEST_CHECK_D88_DISKTYPE_EQUAL(img, 80, 2, 16, 256, D88_DISK_TYPE_2DD);
  TEST_CHECK_D88_DISKTYPE_EQUAL(img, 77, 2, 8, 1024, D88_DISK_TYPE_2HD);
  TEST_CHECK_D88_DISKTYPE_EQUAL(img, 80, 2, 9, 512, D88_DISK_TYPE_2DD);
  TEST_CHECK_D88_DISKTYPE_EQUAL(img, 80, 1, 9, 512, D88_DISK_TYPE_1DD);
  TEST_CHECK_D88_DISKTYPE_EQUAL(img, 80, 2, 26, 256, D88_DISK_TYPE_2HD);
  TEST_CHECK_D88_DISKTYPE_EQUAL(img, 80, 2, 15, 512, D88_DISK_TYPE_2HD);
  TEST_CHECK_D88_DISKTYPE_EQUAL(img, 80, 2, 18, 512, D88_DISK_TYPE_2HD);

  BOOST_CHECK(fdt_image_delete(img));
}
