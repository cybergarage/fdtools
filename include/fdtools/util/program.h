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

#ifndef _FDTOOLS_UTIL_ARGUMENTS_H_
#define _FDTOOLS_UTIL_ARGUMENTS_H_

#include <fdtools/error.h>

#include <fdtools/util/dictionary.h>
#include <fdtools/util/list.h>
#include <fdtools/util/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  FDT_LIST_STRUCT_MEMBERS
  FdtString* value;
} FdtProgramArgument, FdtProgramArguments;

FdtProgramArguments* fdt_program_arguments_new();
bool fdt_program_arguments_delete(FdtProgramArguments*);
bool fdt_program_arguments_add(FdtProgramArguments*, const char*);

#define fdt_program_arguments_size(args) fdt_list_size((FdtList*)args)
#define fdt_program_arguments_gets(args) ((FdtProgramArgument*)fdt_list_gets((FdtList*)args))
#define fdt_program_arguments_get(args, n) ((FdtProgramArgument*)fdt_list_get((FdtList*)args, n))
#define fdt_program_arguments_clear(args) fdt_list_clear((FdtList*)args, (FDT_LIST_DESTRUCTORFUNC)fdt_program_argument_delete)

FdtProgramArgument* fdt_program_argument_new();
bool fdt_program_argument_delete(FdtProgramArgument*);

#define fdt_program_argument_setvalue(arg, v) fdt_string_setvalue(arg->value, v)
#define fdt_program_argument_getvalue(arg) fdt_string_getvalue(arg->value)

typedef struct {
  FdtString* name;
  FdtString* value;
  FdtString* desc;
  bool enabled;
  bool paramRequired;
} FdtProgramOption;

FdtProgramOption* fdt_program_option_new();
bool fdt_program_option_delete(FdtProgramOption*);

#define fdt_program_option_setname(opt, v) fdt_string_setvalue(opt->name, v)
#define fdt_program_option_setdescription(opt, v) fdt_string_setvalue(opt->desc, v)
#define fdt_program_option_setenabled(opt, v) (opt->enabled = v)
#define fdt_program_option_setparameter(opt, v) fdt_string_setvalue(opt->value, v)
#define fdt_program_option_setparameterrequired(opt, v) (opt->paramRequired = v)

#define fdt_program_option_getname(opt) fdt_string_getvalue(opt->name)
#define fdt_program_option_getdescription(opt) fdt_string_getvalue(opt->desc)
#define fdt_program_option_getparameter(opt) fdt_string_getvalue(opt->value)
#define fdt_program_option_isparameterrequired(opt) (opt->paramRequired)

typedef struct {
  FdtString* name;
  FdtProgramArguments* args;
  FdtDictionary* options;
} FdtProgram;

FdtProgram* fdt_program_new();
bool fdt_program_delete(FdtProgram*);
bool fdt_program_addoption(FdtProgram*, const char*, const char*, bool);
bool fdt_program_parse(FdtProgram*, int argc, char* argv[], FdtError*);
void fdt_program_printoptionusages(FdtProgram*);

#define fdt_program_setname(prg, v) fdt_string_setvalue(prg->name, v)
#define fdt_program_addargument(prg, v) fdt_program_arguments_add(prg->args, v)

#define fdt_program_getname(prg) fdt_string_getvalue(prg->name)
#define fdt_program_getarguments(prg) fdt_program_arguments_gets(prg->args)
#define fdt_program_getnarguments(prg) fdt_program_arguments_size(prg->args)
#define fdt_program_getargument(prg, n) fdt_program_argument_getvalue(fdt_program_arguments_get(prg->args, n))
#define fdt_program_getoptionelements(prg) (fdt_dictionary_getelements(prg->options))
#define fdt_program_optionelement_next(elem) fdt_dictionary_element_next(elem)
#define fdt_program_getelementoption(elem) ((FdtProgramOption*)fdt_dictionary_element_getvalue(elem))
#define fdt_program_hasoption(prg, name) (fdt_program_getoption(prg, name) ? true : false)
#define fdt_program_getoption(prg, name) ((FdtProgramOption*)fdt_dictionary_element_getvalue(fdt_dictionary_get(prg->options, name)))
#define fdt_program_getoptionparameter(prg, name) fdt_program_option_getparameter(fdt_program_getoption(prg, name))

#ifdef __cplusplus

} /* extern "C" */

#endif

#endif
