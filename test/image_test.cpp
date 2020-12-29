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

#include "image_test.h"

BOOST_AUTO_TEST_CASE(ImageConfigTest)
{
  FdtImageConfig* config = fdt_image_config_new();
  BOOST_REQUIRE(config);

  BOOST_CHECK(!fdt_image_config_isvalid(config, NULL));
  BOOST_CHECK(fdt_image_config_delete(config));
}

BOOST_AUTO_TEST_CASE(ImageGenerateTest)
{
  FdtImage* img = fdt_image_new();
  BOOST_REQUIRE(img);

  BOOST_REQUIRE(!fdt_image_generatesectors(img, NULL));

  fdt_image_setnumberofcylinder(img, 80);
  fdt_image_setnumberofhead(img, 2);
  fdt_image_setnumberofsector(img, 18);
  fdt_image_setsectorsize(img, 512);
  BOOST_CHECK(fdt_image_generatesectors(img, NULL));

  BOOST_CHECK(fdt_image_delete(img));
}

void ImageLorderComareTest(boost::filesystem::path& filepath, FDT_TEST_IMAGE_NEW_FUNC image_lorder_new, FDT_TEST_IMAGE_NEW_FUNC image_expoter_new)
{
  FdtError* err = fdt_error_new();

  // Loader test

  FdtImage* src_img = image_lorder_new();
  BOOST_REQUIRE(src_img);
  BOOST_REQUIRE(fdt_image_open(src_img, filepath.c_str(), FDT_FILE_READ, err));
  BOOST_REQUIRE(fdt_image_load(src_img, err));
  //fdt_image_print(src_img);
  BOOST_CHECK(fdt_image_close(src_img, err));

  // Exporter test

  size_t img_size = fdt_image_getsize(src_img);

  byte_t* dst_img_buf = (byte_t*)malloc(img_size);
  FILE* mem_fp = fdt_file_memopen(dst_img_buf, img_size, FDT_FILE_WRITE);
  BOOST_REQUIRE(mem_fp);
  fdt_image_file_setfile(src_img, mem_fp);
  BOOST_REQUIRE(fdt_image_export(src_img, err));
  BOOST_CHECK(fdt_image_close(src_img, err));

  // Compare test

  mem_fp = fdt_file_memopen(dst_img_buf, img_size, FDT_FILE_READ);
  BOOST_REQUIRE(mem_fp);
  FdtImage* dst_img = image_expoter_new();
  BOOST_REQUIRE(dst_img);
  fdt_image_file_setfile(dst_img, mem_fp);
  BOOST_REQUIRE(fdt_image_load(dst_img, err));
  BOOST_CHECK(fdt_image_close(dst_img, err));
  BOOST_CHECK(fdt_image_equals(src_img, dst_img));

  free(dst_img_buf);

  // Clean up

  fdt_image_delete(dst_img);
  fdt_image_delete(src_img);

  fdt_error_delete(err);
}
