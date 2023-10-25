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

#include "helper/image.h"

BOOST_AUTO_TEST_CASE(DosFat)
{
  BOOST_CHECK_EQUAL(sizeof(FdtFatBpb), 36);
  BOOST_CHECK_EQUAL(sizeof(FdtFatBpbExtended), (512 - sizeof(FdtFatBpb)));
}

BOOST_AUTO_TEST_CASE(Dos35Format)
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

  if (!fdt_image_equals(img, org_img, err)) {
    ImageCompareDump(org_img, img, err);
  }

  BOOST_CHECK(fdt_error_delete(err));
  BOOST_CHECK(fdt_image_delete(img));
  BOOST_CHECK(fdt_image_delete(org_img));
}
