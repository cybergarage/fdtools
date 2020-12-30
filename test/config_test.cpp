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

#include <fdtools/img/config.h>

BOOST_AUTO_TEST_CASE(ConfigCopyTest)
{
  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  FdtImageConfig* config = fdt_image_config_new();
  BOOST_REQUIRE(config);
  fdt_image_config_setname(config, "/dev/fd0");
  fdt_image_config_setnumberofcylinder(config, 80);
  fdt_image_config_setnumberofhead(config, 2);
  fdt_image_config_setnumberofsector(config, 18);
  fdt_image_config_setsectorsize(config, 512);

  FdtImageConfig* other = fdt_image_config_copy(config);
  BOOST_REQUIRE(config);

  BOOST_CHECK_MESSAGE(fdt_image_config_equals(config, other, err), fdt_error_getdebugmessage(err));

  BOOST_CHECK(fdt_image_config_delete(config));
  BOOST_CHECK(fdt_image_config_delete(other));

  BOOST_CHECK(fdt_error_delete(err));
}
