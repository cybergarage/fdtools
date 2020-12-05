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

#include <unistd.h>

#include <fdtools/util/program.h>

FdtProgram* fdt_program_new()
{
  FdtProgram* prg = (FdtProgram*)malloc(sizeof(FdtProgram));
  if (!prg) {
    return NULL;
  }

  prg->name = fdt_string_new();
  prg->args = fdt_program_arguments_new();
  prg->options = fdt_dictionary_new();
  if (!prg->name || !prg->args || !prg->options) {
    fdt_program_delete(prg);
    return NULL;
  }

  return prg;
}

bool fdt_program_delete(FdtProgram* prg)
{
  if (!prg)
    return false;
  fdt_string_delete(prg->name);
  fdt_program_arguments_delete(prg->args);
  fdt_dictionary_delete(prg->options);
  free(prg);
  return true;
}

bool fdt_program_parse(FdtProgram* prg, int argc, char* const argv[])
{
  FdtString* opt_strs = fdt_string_new();
  if (!opt_strs)
    return false;

  for (FdtProgramOption* opt = fdt_program_getoptions(prg); opt; opt = fdt_program_option_next(opt)) {
    if (!fdt_string_addvalue(opt_strs, fdt_program_option_getname(opt)))
      return false;
    if (fdt_program_option_isparameterrequired(opt)) {
      if (!fdt_string_addvalue(opt_strs, ":"))
        return false;
    }
  }

  // Sets program name

  fdt_program_setname(prg, argv[0]);

  // Parses option parameters

  char opt_str[2] = { 0x00, 0x00 };
  int opt_ch;
  while ((opt_ch = getopt(argc, argv, fdt_string_getvalue(opt_strs))) != -1) {
    opt_str[0] = opt_ch;
    FdtProgramOption* opt = fdt_program_getoption(prg, opt_str);
    if (!opt)
      return false;
    fdt_program_option_setenabled(opt, true);
    if (fdt_program_option_isparameterrequired(opt)) {
      fdt_program_option_setparameter(opt, optarg);
    }
  }

  // Adds non option arguments

  while (optind < argc) {
    fdt_program_addargument(prg, argv[optind]);
    optind++;
  }

  return true;
}
