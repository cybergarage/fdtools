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

const char* fdt_program_getname(FdtProgram* prg)
{
  if (!prg)
    return "";
  const char* prg_name = fdt_string_getvalue(prg->name);
  ssize_t path_idx = fdt_strrchr(prg_name, "./", 2);
  if (path_idx < 0) {
    return prg_name;
  }
  return (prg_name + (path_idx + 1));
}

bool fdt_program_addoption(FdtProgram* prg, const char* name, const char* desc, bool hasParam, const char* default_value)
{
  if (!prg)
    return false;

  FdtProgramOption* opt = fdt_program_option_new();
  if (!opt)
    return false;

  fdt_program_option_setname(opt, name);
  fdt_program_option_setdescription(opt, desc);
  fdt_program_option_setparameterrequired(opt, hasParam);
  fdt_program_option_setparameter(opt, default_value);

  return fdt_dictionary_setvalue(prg->options, name, opt, (FDT_DICTIONARY_ELEMENT_DESTRUCTORFUNC)fdt_program_option_delete);
}

bool fdt_program_parse(FdtProgram* prg, int argc, char* argv[], FdtError* err)
{
  if (!prg)
    return false;

  FdtString* opt_strs = fdt_string_new();
  if (!opt_strs)
    return false;

  fdt_string_setvalue(opt_strs, "");
  for (FdtDictionaryElement* elem = fdt_program_getoptionelements(prg); elem; elem = fdt_program_optionelement_next(elem)) {
    FdtProgramOption* opt = fdt_program_getelementoption(elem);

    if (!fdt_string_appendvalue(opt_strs, fdt_program_option_getname(opt)))
      return false;
    if (fdt_program_option_isparameterrequired(opt)) {
      if (!fdt_string_appendvalue(opt_strs, ":"))
        return false;
    }
  }

  // Sets program name

  fdt_program_setname(prg, argv[0]);

  // Parses option parameters

  char opt_str[2] = { 0x00, 0x00 };
  int opt_ch;
  opterr = 0;
  while ((opt_ch = getopt(argc, argv, fdt_string_getvalue(opt_strs))) != -1) {
    opt_str[0] = opt_ch;
    FdtProgramOption* opt = fdt_program_getoption(prg, opt_str);
    if (!opt) {
      fdt_error_setmessage(err, "invalid option '%c'", optopt);
      return false;
    }
    fdt_program_option_setenabled(opt, true);
    if (fdt_program_option_isparameterrequired(opt)) {
      fdt_program_option_setparameter(opt, optarg);
    }
  }

  // Adds non option arguments1

  while (optind < argc) {
    fdt_program_addargument(prg, argv[optind]);
    optind++;
  }

  return true;
}

bool fdt_program_isoptionenabled(FdtProgram* prg, const char* name)
{
  if (!prg)
    return false;

  FdtProgramOption* opt = fdt_program_getoption(prg, name);
  if (!opt)
    return false;

  return fdt_program_option_isenabled(opt);
}

const char* fdt_program_getoptionstring(FdtProgram* prg, const char* name)
{
  FdtProgramOption* opt = fdt_program_getoption(prg, name);
  if (!opt)
    return NULL;
  return fdt_program_option_getparameter(opt);
}

int fdt_program_getoptioninteger(FdtProgram* prg, const char* name)
{
  const char* optstr = fdt_program_getoptionstring(prg, name);
  if (!optstr)
    return 0;
  return atoi(optstr);
}

void fdt_program_printoptionusages(FdtProgram* prg)
{
  if (!prg)
    return;

  for (FdtDictionaryElement* elem = fdt_program_getoptionelements(prg); elem; elem = fdt_program_optionelement_next(elem)) {
    FdtProgramOption* opt = (FdtProgramOption*)fdt_dictionary_element_getvalue(elem);
    printf("-%s %s\n", fdt_program_option_getname(opt), fdt_program_option_getdescription(opt));
  }
}
