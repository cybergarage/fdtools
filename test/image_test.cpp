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
#include <fdtools/img/image.h>

#include "helper/image.h"

BOOST_AUTO_TEST_CASE(ImageConfig)
{
  FdtImageConfig* config = fdt_image_config_new();
  BOOST_REQUIRE(config);

  BOOST_CHECK(!fdt_image_config_isvalid(config, NULL));
  BOOST_CHECK(fdt_image_config_delete(config));
}

BOOST_AUTO_TEST_CASE(ImageGenerate)
{
  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  FdtImage* img = fdt_image_new();
  BOOST_REQUIRE(img);

  BOOST_REQUIRE_MESSAGE(!fdt_image_generatesectors(img, err), fdt_error_getdebugmessage(err));

  fdt_image_setnumberofcylinder(img, 80);
  fdt_image_setnumberofhead(img, 2);
  fdt_image_setnumberofsector(img, 18);
  fdt_image_setsectorsize(img, 512);

  BOOST_CHECK_MESSAGE(fdt_image_generatesectors(img, err), fdt_error_getdebugmessage(err));

  BOOST_CHECK(fdt_image_delete(img));

  BOOST_CHECK(fdt_error_delete(err));
}

BOOST_AUTO_TEST_CASE(ImageSortSectors)
{
  FdtImage* img = fdt_image_new();
  BOOST_REQUIRE(img);

  size_t number_of_cylinder = 80;
  size_t number_of_head = 2;
  size_t number_of_sector = 18;

  for (ssize_t c = (number_of_cylinder - 1); 0 <= c; c--) {
    for (ssize_t h = (number_of_head - 1); 0 <= h; h--) {
      for (ssize_t s = number_of_sector; 1 <= s; s--) {
        FdtImageSector* sector = fdt_image_sector_new();
        BOOST_REQUIRE(sector);
        fdt_image_sector_setcylindernumber(sector, c);
        fdt_image_sector_setheadnumber(sector, h);
        fdt_image_sector_setnumber(sector, s);
        fdt_image_addsector(img, sector);
      }
    }
  }

  BOOST_CHECK(!fdt_image_issectorssorted(img));

  BOOST_REQUIRE(fdt_image_sortsectors(img));
  BOOST_CHECK(fdt_image_issectorssorted(img));

  BOOST_CHECK(fdt_image_delete(img));
}

BOOST_AUTO_TEST_CASE(ImageImport)
{
  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  FdtImage* src_img = fdt_image_new();
  BOOST_REQUIRE(src_img);
  fdt_image_setnumberofcylinder(src_img, 80);
  fdt_image_setnumberofhead(src_img, 2);
  fdt_image_setnumberofsector(src_img, 18);
  fdt_image_setsectorsize(src_img, 512);
  BOOST_REQUIRE(fdt_image_generatesectors(src_img, NULL));
  size_t sector_no = 1;
  for (FdtImageSector* sector = fdt_image_getsectors(src_img); sector; sector = fdt_image_sector_next(sector)) {
    size_t sector_size = sector_no;
    byte_t* sector_data = (byte_t*)calloc(sector_size, 1);
    sector_data[0] = sector_no;
    fdt_image_sector_setsize(sector, sector_size);
    fdt_image_sector_setdata(sector, sector_data);
  }

  FdtImage* dst_img = fdt_image_new();
  BOOST_REQUIRE(dst_img);
  BOOST_REQUIRE_MESSAGE(fdt_image_import(dst_img, src_img, err), fdt_error_getdebugmessage(err));
  BOOST_CHECK_MESSAGE(fdt_image_equals(src_img, dst_img, err), fdt_error_getdebugmessage(err));
  BOOST_CHECK(fdt_image_delete(dst_img));

  BOOST_CHECK(fdt_image_delete(src_img));

  BOOST_CHECK(fdt_error_delete(err));
}
