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

#include <fdtools/dev/device.h>

BOOST_AUTO_TEST_CASE(FloppyParamsTest)
{
  FdtFloppyParams* params = fdt_floppy_params_new();
  BOOST_CHECK(params);
  BOOST_CHECK(fdt_floppy_params_delete(params));
}

BOOST_AUTO_TEST_CASE(FloppyGetParamsTest)
{
  const char* TEST_DEV = "/dev/fd0";
  FdtDevice* dev = fdt_device_new();
  BOOST_CHECK(dev);
  FdtError* err = fdt_error_new();
  BOOST_CHECK(err);
  FdtFloppyParams* fdparams = fdt_floppy_params_new();
  BOOST_CHECK(fdparams);

  BOOST_CHECK(fdt_device_open(dev, TEST_DEV, FDT_DEVICE_READ, err));

  BOOST_CHECK(fdt_device_getfloppyparameters(dev, fdparams, err));

  BOOST_CHECK(fdt_device_delete(dev));
  BOOST_CHECK(fdt_floppy_params_delete(fdparams));
  BOOST_CHECK(fdt_error_delete(err));
}