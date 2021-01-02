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

void ImageLoarderExporterCompareTest(boost::filesystem::path& filepath, FDT_TEST_IMAGE_NEW_FUNC image_new_func)
{
  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  // Loader test

  FdtImage* src_img = image_new_func();
  BOOST_REQUIRE(src_img);
  fdt_image_setname(src_img, filepath.c_str());
  BOOST_REQUIRE_MESSAGE(fdt_image_load(src_img, err), fdt_error_getdebugmessage(err));

  // Exporter test

  size_t img_size = fdt_image_getsize(src_img);
  BOOST_CHECK(0 < img_size);

  byte_t* dst_img_buf = (byte_t*)malloc(img_size);
  FILE* mem_fp = fdt_file_memopen(dst_img_buf, img_size, FDT_FILE_WRITE);
  BOOST_REQUIRE(mem_fp);
  fdt_image_file_setfile(src_img, mem_fp);
  BOOST_REQUIRE_MESSAGE(fdt_image_export(src_img, err), fdt_error_getdebugmessage(err));
  BOOST_CHECK_MESSAGE(fdt_image_close(src_img, err), fdt_error_getdebugmessage(err));

  // Compare test

  mem_fp = fdt_file_memopen(dst_img_buf, img_size, FDT_FILE_READ);
  BOOST_REQUIRE(mem_fp);
  FdtImage* dst_img = image_new_func();
  BOOST_REQUIRE(dst_img);
  fdt_image_file_setfile(dst_img, mem_fp);
  BOOST_REQUIRE_MESSAGE(fdt_image_load(dst_img, err), fdt_error_getdebugmessage(err));
  BOOST_CHECK_MESSAGE(fdt_image_close(dst_img, err), fdt_error_getdebugmessage(err));
  BOOST_CHECK_MESSAGE(fdt_image_equals(src_img, dst_img, err), fdt_error_getdebugmessage(err));

  free(dst_img_buf);

  // Cleanup

  BOOST_CHECK(fdt_image_delete(dst_img));
  BOOST_CHECK(fdt_image_delete(src_img));
  BOOST_CHECK(fdt_error_delete(err));
}

void ImageExportTest(FdtImage* img, FDT_TEST_IMAGE_NEW_FUNC export_image_new_func)
{
  const int EXPORT_IMGSIZE_MAX = 8 * 1024 * 1024;

  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  byte_t* export_img_buf = (byte_t*)malloc(EXPORT_IMGSIZE_MAX);
  BOOST_REQUIRE(export_img_buf);
  FILE* mem_fp = fdt_file_memopen(export_img_buf, EXPORT_IMGSIZE_MAX, FDT_FILE_WRITE);
  BOOST_REQUIRE(mem_fp);

  // Import test

  FdtImage* export_img = export_image_new_func();
  BOOST_REQUIRE_MESSAGE(fdt_image_import(export_img, img, err), fdt_error_getdebugmessage(err));

  // Export test

  fdt_image_file_setfile(export_img, mem_fp);
  BOOST_CHECK(fdt_image_delete(export_img));
  BOOST_REQUIRE_MESSAGE(fdt_image_export(export_img, err), fdt_error_getdebugmessage(err));
  BOOST_CHECK_MESSAGE(fdt_image_close(export_img, err), fdt_error_getdebugmessage(err));
  free(export_img_buf);

  // Cleanup

  BOOST_CHECK(fdt_error_delete(err));
}
