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

#include "image_test.h"

const char* TEST_FLOPPY_DEV = "/dev/fd0";

BOOST_AUTO_TEST_CASE(FloppyParamsTest)
{
  FdtFloppyParams* params = fdt_floppy_params_new();
  BOOST_REQUIRE(params);
  BOOST_CHECK(fdt_floppy_params_delete(params));
}

BOOST_AUTO_TEST_CASE(FloppyGetParamsTest)
{
  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  FdtDevice* dev = fdt_device_new();
  BOOST_REQUIRE(dev);
  FdtFloppyParams* fdparams = fdt_floppy_params_new();
  BOOST_REQUIRE(fdparams);

  if (!fdt_device_open(dev, TEST_FLOPPY_DEV, FDT_FILE_READ, err)) {
    BOOST_CHECK(fdt_error_delete(err));
    return;
  }

  BOOST_CHECK(fdt_device_getfloppyparameters(dev, fdparams, err));

  BOOST_CHECK(fdt_device_delete(dev));
  BOOST_CHECK(fdt_floppy_params_delete(fdparams));
  BOOST_CHECK(fdt_error_delete(err));
}

BOOST_AUTO_TEST_CASE(FloppyImportTest)
{
  FdtError* err = fdt_error_new();
  BOOST_REQUIRE(err);

  FdtFloppyParams* fdparams = fdt_floppy_params_new();
  BOOST_CHECK(fdparams);

  // Gets current floppy parameters

  FdtDevice* dev = fdt_device_new();
  BOOST_REQUIRE(dev);
  if (!fdt_device_open(dev, TEST_FLOPPY_DEV, FDT_FILE_READ, err))
    return;

  BOOST_REQUIRE_MESSAGE(fdt_device_getfloppyparameters(dev, fdparams, err), fdt_error_getdebugmessage(err));
  BOOST_CHECK(fdt_device_delete(dev));

  // Imports floppy image

  FdtDeviceImage* dev_img = (FdtDeviceImage*)fdt_device_image_new();
  BOOST_REQUIRE(dev_img);
  BOOST_REQUIRE_MESSAGE(fdt_device_image_setfloppyparams(dev_img, fdparams, err), fdt_error_getdebugmessage(err));
  BOOST_REQUIRE_MESSAGE(fdt_device_image_generatesectors(dev_img, err), fdt_error_getdebugmessage(err));
  BOOST_REQUIRE_MESSAGE(fdt_device_image_open(dev_img, TEST_FLOPPY_DEV, FDT_FILE_READ, err), fdt_error_getdebugmessage(err));
  BOOST_REQUIRE_MESSAGE(fdt_device_image_load(dev_img, err), fdt_error_getdebugmessage(err));
  BOOST_CHECK_MESSAGE(fdt_device_image_close(dev_img, err), fdt_error_getdebugmessage(err));

  // Exports a imported floppy image to all plugin images

  for (FdtImagePlugin* plg = fdt_image_plugins_getallimagers(); plg; plg = fdt_image_plugin_next(plg)) {
    FDT_IMAGE_IMAGER imager = fdt_image_plugin_getimager(plg);
    ImageExportCompareTest((FdtImage*)dev_img, imager);
  }

  // Cleanup
  BOOST_CHECK(fdt_floppy_params_delete(fdparams));
  BOOST_CHECK(fdt_error_delete(err));
}

#endif /* __linux__ */
