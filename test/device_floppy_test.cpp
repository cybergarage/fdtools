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

const char* TEST_FLOPPY_DEV = "/dev/fd0";

BOOST_AUTO_TEST_CASE(FloppyParamsTest)
{
  FdtFloppyParams* params = fdt_floppy_params_new();
  BOOST_CHECK(params);
  BOOST_CHECK(fdt_floppy_params_delete(params));
}

BOOST_AUTO_TEST_CASE(FloppyGetParamsTest)
{
  FdtDevice* dev = fdt_device_new();
  BOOST_CHECK(dev);
  FdtError* err = fdt_error_new();
  BOOST_CHECK(err);
  FdtFloppyParams* fdparams = fdt_floppy_params_new();
  BOOST_CHECK(fdparams);

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
  const char* TEST_FLOPPY_DEV = "/dev/fd0";
  FdtDevice* dev = fdt_device_new();
  BOOST_CHECK(dev);
  FdtError* err = fdt_error_new();
  BOOST_CHECK(err);
  FdtFloppyParams* fdparams = fdt_floppy_params_new();
  BOOST_CHECK(fdparams);

  if (!fdt_device_open(dev, TEST_FLOPPY_DEV, FDT_FILE_READ, err)) {
    BOOST_CHECK(fdt_error_delete(err));
    return;
  }

  BOOST_CHECK(fdt_device_getfloppyparameters(dev, fdparams, err));

  BOOST_CHECK(fdt_device_delete(dev));
  BOOST_CHECK(fdt_floppy_params_delete(fdparams));
  BOOST_CHECK(fdt_error_delete(err));
}

#endif
