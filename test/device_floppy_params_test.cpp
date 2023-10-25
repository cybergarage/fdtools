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

#if defined(__linux__)

#include <boost/test/unit_test.hpp>

#include <fdtools/dev/device.h>
#include <fdtools/dev/image.h>

BOOST_AUTO_TEST_CASE(FloppySet525InchParams)
{
  // getfdprm parameters
  // DS HD tpi=96 size=2400 sect=15 dtr=0 perp=0 fm=0 cyl=80 ssize=512 gap=0x1b fmt_gap=0x6c spec1=0x00 (AT/HD)
  // DS HD tpi=96 size=2464 sect=8 dtr=0 perp=0 fm=0 cyl=77 ssize=1KB gap=0x1b fmt_gap=0x6c spec1=0x00  (98/HD)
  // DS DD tpi=48 size=640 sect=16 dtr=1DD perp=0 fm=0 cyl=40 ssize=256 gap=0x23 fmt_gap=0x46 spec1=0x00 (X68/HD)
  // DS DD tpi=48 size=640 sect=16 dtr=1 perp=0 fm=0 cyl=40 ssize=256 gap=0x23 fmt_gap=0x46 spec1=0x00 (X1,88/2D)
  // DS HD tpi=96 size=2080 sect=26 dtr=0 perp=0 fm=0 cyl=80 ssize=256 gap=0x1b fmt_gap=0x50 spec1=0x00 (88/HD)
  // DS HD tpi=96 size=1232 sect=16 dtr=0 perp=0 fm=0 cyl=77 ssize=256 gap=0x1b fmt_gap=0x6c spec1=0x00 (X1/HD)
  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  BOOST_CHECK(fdt_error_delete(err));
}

BOOST_AUTO_TEST_CASE(FloppySet35InchParams)
{
  // getfdprm parameters
  // DS HD stretch=0 size=2880 sect=18 dtr=0 perp=0 fm=0 cyl=80 ssize=512 gap=0x1b fmt_gap=0x6c spec1=0x00 (AT/HD)
  // DS HD stretch=0 size=2464 sect=8 dtr=0 perp=0 fm=0 cyl=77 ssize=1KB gap=0x1b fmt_gap=0x6c spec1=0x00  (98/HD)
  // DS HD stretch=0 size=2880 sect=18 dtr=0 perp=0 fm=0 cyl=80 ssize=512 gap=0x1b fmt_gap=0x6c spec1=0xcf (FM/2D)
  // DS DD stretch=0 size=1280 sect=16 dtr=2 perp=0 fm=0 cyl=80 ssize=256 gap=0x2a fmt_gap=0x46 spec1=0x00 (FM/2DD)
  // DS DD stretch=0 size=1440 sect=9 dtr=2 perp=0 fm=0 cyl=80 ssize=512 gap=0x2a fmt_gap=0x6c spec1=0x00 (MSX/2DD)
  // SS DD stretch=0 size=720 sect=9 dtr=2 perp=0 fm=0 cyl=80 ssize=512 gap=0x2a fmt_gap=0x6c spec1=0x00 (MSX/1DD)
  // DS DD stretch=0 size=1280 sect=16 dtr=2 perp=0 fm=0 cyl=80 ssize=256 gap=0x2a fmt_gap=0x46 spec1=0x00 (MZ/2DD)
  // SS DD stretch=0 size=560 sect=16 dtr=2 perp=0 fm=0 cyl=70 ssize=256 gap=0x2a fmt_gap=0x46 spec1=0x00  (SMC777/1DD)
  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  BOOST_CHECK(fdt_error_delete(err));
}

#endif
