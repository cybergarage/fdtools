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

#include <fdtools/util/array.h>
#include <fdtools/util/program.h>

BOOST_AUTO_TEST_CASE(Error)
{
  FdtError* err = fdt_error_new();
  BOOST_CHECK(err);
  BOOST_CHECK(!fdt_error_iserror(err));
  BOOST_CHECK(fdt_error_delete(err));
}

BOOST_AUTO_TEST_CASE(ErrorNull)
{
  BOOST_CHECK(!fdt_error_setmessage(NULL, ""));
}
