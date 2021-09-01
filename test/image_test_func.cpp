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

void ImageExportCompareTest(FdtImage* img, FDT_IMAGE_IMAGER convert_imager)
{
  const size_t EXPORT_IMGSIZE_MAX = 8 * 1024 * 1024;

  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  // Allocs the export memory

  size_t export_img_buf_size = EXPORT_IMGSIZE_MAX;
  byte_t* export_img_buf = (byte_t*)malloc(export_img_buf_size);
  BOOST_CHECK(export_img_buf);

  // Exports the loaded image to a memory file

  BOOST_TEST_MESSAGE("Exporting -> " << fdt_image_getname(img) << "(" << fdt_image_gettypeid(img) << "/MEM)");

  FdtImage* export_img = convert_imager();
  BOOST_REQUIRE(export_img);
  BOOST_CHECK_MESSAGE(fdt_image_import(export_img, img, err), fdt_error_getdebugmessage(err));
  FILE* mem_fp = fdt_file_memopen(export_img_buf, export_img_buf_size, FDT_FILE_WRITE);
  BOOST_REQUIRE(mem_fp);
  fdt_image_file_setfile(export_img, mem_fp);
  BOOST_REQUIRE_MESSAGE(fdt_image_export(export_img, err), fdt_error_getdebugmessage(err));
  BOOST_CHECK_MESSAGE(fdt_image_close(export_img, err), fdt_error_getdebugmessage(err));

  BOOST_TEST_MESSAGE("Expoted   -> " << fdt_image_getname(img) << "(" << fdt_image_gettypeid(img) << "/MEM)");

  // Loads the exported memory file

  BOOST_TEST_MESSAGE("Loading   <- " << fdt_image_getname(img) << "(" << fdt_image_gettypeid(img) << "/MEM)");

  mem_fp = fdt_file_memopen(export_img_buf, export_img_buf_size, FDT_FILE_READ);
  BOOST_REQUIRE(mem_fp);
  FdtImage* exported_img = convert_imager();
  BOOST_REQUIRE(exported_img);
  fdt_image_file_setfile(exported_img, mem_fp);
  BOOST_REQUIRE_MESSAGE(fdt_image_load(exported_img, err), fdt_error_getdebugmessage(err));
  BOOST_CHECK_MESSAGE(fdt_image_close(exported_img, err), fdt_error_getdebugmessage(err));

  BOOST_TEST_MESSAGE("Loaded    <- " << fdt_image_getname(img) << "(" << fdt_image_gettypeid(img) << "/MEM)");

  // Compare test

  BOOST_CHECK_MESSAGE(fdt_image_equals(img, exported_img, err), fdt_error_getdebugmessage(err));
  BOOST_TEST_MESSAGE("Compared     " << fdt_image_getname(img) << "(" << fdt_image_gettypeid(img) << ")<->" << fdt_image_getname(exported_img) << "(" << fdt_image_gettypeid(exported_img) << "/MEM)");

  // Cleaning

  BOOST_REQUIRE(fdt_image_delete(export_img));
  BOOST_REQUIRE(fdt_image_delete(exported_img));
  free(export_img_buf);

  BOOST_CHECK(fdt_error_delete(err));
}
