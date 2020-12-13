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

BOOST_AUTO_TEST_CASE(ProgramParseTest)
{
  const char* TEST_PRG_ARGS[] = { "prg", "-c", "40", "-h", "2", "-s", "16", "-v", "/dev/fd0" };

  FdtError* err = fdt_error_new();

  FdtProgram* prg = fdt_program_new();
  BOOST_CHECK(prg);

  BOOST_CHECK(fdt_program_addoption(prg, "c", true));
  BOOST_CHECK(fdt_program_addoption(prg, "h", true));
  BOOST_CHECK(fdt_program_addoption(prg, "s", true));
  BOOST_CHECK(fdt_program_addoption(prg, "v", false));

  BOOST_CHECK(fdt_program_hasoption(prg, "c"));
  BOOST_CHECK(fdt_program_hasoption(prg, "h"));
  BOOST_CHECK(fdt_program_hasoption(prg, "s"));
  BOOST_CHECK(fdt_program_hasoption(prg, "v"));

  BOOST_CHECK(fdt_program_parse(prg, fdt_array_countof(TEST_PRG_ARGS), (char**)TEST_PRG_ARGS, err));

  BOOST_CHECK(fdt_program_delete(prg));

  BOOST_CHECK(fdt_error_delete(err));
}
