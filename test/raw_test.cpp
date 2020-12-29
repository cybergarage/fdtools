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

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include <fdtools/img/file.h>
#include <fdtools/img/raw.h>
#include <fdtools/util/array.h>

const std::string TEST_IMAGE_DIRECTORY = "./img";

BOOST_AUTO_TEST_CASE(RAWImageLoaderTest)
{
  const char TEST_RAW_IMAGES[][64] = {
    "test-001.raw",
    "test-001.img",
  };

  FdtError* err = fdt_error_new();

  for (int n = 0; n < fdt_array_countof(TEST_RAW_IMAGES); n++) {
    std::string filename = TEST_IMAGE_DIRECTORY + "/" + TEST_RAW_IMAGES[n];
    boost::filesystem::path filepath(filename);
    if (!boost::filesystem::exists(filepath))
      continue;

    BOOST_CHECK_EQUAL(fdt_image_name_gettype(filename.c_str()), FDT_IMAGE_TYPE_RAW);

    // Loader test

    FdtImage* src_img = fdt_raw_image_new();
    BOOST_CHECK(src_img);
    BOOST_CHECK(fdt_image_open(src_img, filename.c_str(), FDT_FILE_READ, err));
    BOOST_CHECK(fdt_image_load(src_img, err));
    //fdt_image_print(src_img);
    BOOST_CHECK(fdt_image_close(src_img, err));

    // Exporter test

    size_t img_size = fdt_image_getsize(src_img);

    byte_t* dst_img_buf = (byte_t*)malloc(img_size);
    FILE* mem_fp = fdt_file_memopen(dst_img_buf, img_size, FDT_FILE_WRITE);
    fdt_image_file_setfile(src_img, mem_fp);
    BOOST_CHECK(fdt_image_export(src_img, err));
    BOOST_CHECK(fdt_image_close(src_img, err));

    // Compare test

    mem_fp = fdt_file_memopen(dst_img_buf, img_size, FDT_FILE_READ);
    FdtImage* dst_img = fdt_raw_image_new();
    fdt_image_file_setfile(dst_img, mem_fp);
    BOOST_CHECK(fdt_image_load(dst_img, err));
    BOOST_CHECK(fdt_image_close(dst_img, err));
    BOOST_CHECK(fdt_image_equals(src_img, dst_img));

    free(dst_img_buf);

    // Clean up

    fdt_image_delete(dst_img);
    fdt_image_delete(src_img);
  }

  fdt_error_delete(err);
}
