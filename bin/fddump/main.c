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

#include <stdio.h>
#include <stdlib.h>

#include <fdtools/util/program.h>

void print_usage(FdtProgram* prg)
{
  printf("Usage: %s\n", fdt_program_getname(prg));
  fdt_program_printoptionusages(prg);
}

void print_error(FdtError* err)
{
  printf("Error: %s\n", fdt_error_getmessage(err));
}

int main(int argc, char* argv[])
{
  FdtError* err = fdt_error_new();
  if (!err)
    return EXIT_FAILURE;

  FdtProgram* prg = fdt_program_new();
  if (!prg)
    return EXIT_FAILURE;
  fdt_program_addoption(prg, "c", "", true);
  fdt_program_addoption(prg, "h", "", true);
  fdt_program_addoption(prg, "s", "", true);
  fdt_program_addoption(prg, "v", "", false);

  if (!fdt_program_parse(prg, argc, argv, err)) {
    print_error(err);
    print_usage(prg);
    return EXIT_FAILURE;
  }

  if (fdt_program_getnarguments(prg) < 2) {
    print_usage(prg);
    return EXIT_FAILURE;
  }

  fdt_program_delete(prg);
  fdt_error_delete(err);

  return 0;
}