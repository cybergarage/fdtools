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

BOOST_AUTO_TEST_CASE(ImageConfigTest)
{
  FdtImageConfig* config = fdt_image_config_new();
  BOOST_CHECK(config);

  BOOST_CHECK(!fdt_image_config_isvalid(config, NULL));
  BOOST_CHECK(fdt_image_config_delete(config));
}

BOOST_AUTO_TEST_CASE(ImageGenerateTest)
{
  FdtImage* img = fdt_image_new();
  BOOST_CHECK(img);

  BOOST_CHECK(!fdt_image_generatesectors(img, NULL));

  fdt_image_setnumberofcylinder(img, 80);
  fdt_image_setnumberofhead(img, 2);
  fdt_image_setnumberofsector(img, 18);
  fdt_image_setsectorsize(img, 512);
  BOOST_CHECK(fdt_image_generatesectors(img, NULL));

  BOOST_CHECK(fdt_image_delete(img));
}
