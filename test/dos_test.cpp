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
#include <fdtools/img/image.h>
#include <fdtools/plugins/fmt/dos/dos.h>
#include <fdtools/plugins/image.h>
#include <fdtools/util/hexdump.h>

BOOST_AUTO_TEST_CASE(DosFatTest)
{
  BOOST_CHECK_EQUAL(sizeof(FdtFatBpb), 36);
  BOOST_CHECK_EQUAL(sizeof(FdtFatBpbExtended), (512 - sizeof(FdtFatBpb)));
}

BOOST_AUTO_TEST_CASE(Dos35FormatTest)
{
  const std::string TEST_DOS_BLANK_IMAGE = "./img/35-2hd-msdos.raw";

  FdtError* err = fdt_error_new();

  FdtImage* img = fdt_image_new();
  BOOST_REQUIRE(img);
  fdt_image_setdensity(img, FDT_IMAGE_DENSITY_HD);
  fdt_image_setnumberofcylinder(img, FDT_DOS_35_FD_CYLINDER);
  fdt_image_setnumberofhead(img, FDT_DOS_35_FD_HEAD);
  fdt_image_setnumberofsector(img, FDT_DOS_35_FD_SECTOR);
  fdt_image_setsectorsize(img, FDT_DOS_35_FD_SECTOR_SIZE);
  BOOST_REQUIRE(fdt_image_generatesectors(img, err));

  FdtFormat* fmt = fdt_dos_from(img, err);
  BOOST_REQUIRE(img);
  BOOST_REQUIRE_MESSAGE(fdt_format_format(fmt, err), fdt_error_getmessage(err));
  BOOST_CHECK(fdt_format_delete(fmt));

  FdtImage* org_img = fdt_image_from(TEST_DOS_BLANK_IMAGE.c_str(), err);
  BOOST_REQUIRE_MESSAGE(org_img, fdt_error_getmessage(err));

  BOOST_CHECK_MESSAGE(fdt_image_equals(img, org_img, err), fdt_error_getmessage(err));

  for (FdtImageSector* sector = fdt_image_sectors_gets(org_img->sectors); sector; sector = fdt_image_sector_next(sector)) {
    size_t t = fdt_image_sector_getcylindernumber(sector);
    size_t h = fdt_image_sector_getheadnumber(sector);
    size_t s = fdt_image_sector_getnumber(sector);
    FdtImageSector* other = fdt_image_sectors_getsector(img->sectors, t, h, s);
    if (!other) {
      continue;
    }

    if (fdt_image_sector_equals(sector, other, err))
      continue;

    byte_t* sector_l_data = fdt_image_sector_getdata(sector);
    size_t sector_l_size = fdt_image_sector_getsize(sector);

    byte_t* sector_r_data = fdt_image_sector_getdata(other);
    size_t sector_r_size = fdt_image_sector_getsize(other);

    fdt_hexdump_compare_print(sector_l_data, sector_l_size, sector_r_data, sector_r_size);

    break;
  }

  BOOST_CHECK(fdt_error_delete(err));
  BOOST_CHECK(fdt_image_delete(img));
  BOOST_CHECK(fdt_image_delete(org_img));
}
