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

BOOST_AUTO_TEST_CASE(FloppySetParamsTest)
{
  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  BOOST_CHECK(fdt_error_delete(err));
}

#endif
