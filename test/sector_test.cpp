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

#include <fdtools/img/sector.h>

BOOST_AUTO_TEST_CASE(SectorCopyTest)
{
  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  FdtImageSector* sector = fdt_image_sector_new();
  BOOST_REQUIRE(sector);
  fdt_image_sector_setcylindernumber(sector, 80);
  fdt_image_sector_setheadnumber(sector, 2);
  fdt_image_sector_setnumber(sector, 18);
  fdt_image_sector_setsize(sector, 512);

  FdtImageSector* other = fdt_image_sector_copy(sector);
  BOOST_REQUIRE(sector);

  BOOST_CHECK_MESSAGE(fdt_image_sector_equals(sector, other, err), fdt_error_getdebugmessage(err));

  BOOST_CHECK(fdt_image_sector_delete(sector));
  BOOST_CHECK(fdt_image_sector_delete(other));

  BOOST_CHECK(fdt_error_delete(err));
}
