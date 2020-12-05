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

#include <fdtools/util/dictionary.h>
#include <fdtools/util/list.h>
#include <fdtools/util/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  FDT_LIST_STRUCT_MEMBERS
  FdtString* value;
} FdtArgument, FdtArgumentList;

FdtArgument* fdt_argument_new();
bool fdt_argument_delete(FdtArgument*);

#define fdt_argument_setvalue(arg, v) fdt_string_setvalue(arg->value, v)
#define fdt_argument_getvalue(arg) fdt_string_getvalue(arg->value)

typedef struct {
  FdtString* name;
  FdtString* value;
  bool enabled;
  bool valueEnabled;
} FdtArgumentOption;

FdtArgumentOption* fdt_argument_option_new();
bool fdt_argument_option_delete(FdtArgumentOption*);

#define fdt_argument_option_setname(opt, v) fdt_string_setvalue(opt->name, v)
#define fdt_argument_option_setvalue(opt, v) fdt_string_setvalue(opt->value, v)
#define fdt_argument_option_setenabled(opt, v) (opt->enabled, v)
#define fdt_argument_option_setvalueenabled(opt, v) (opt->valueEnabled, v)

#define fdt_argument_option_getname(opt) fdt_string_getvalue(opt->name)
#define fdt_argument_option_getvalue(opt) fdt_string_getvalue(opt->value)
#define fdt_argument_option_isenabled(opt) (opt->enabled)
#define fdt_argument_option_isvalueenabled(opt) (opt->valueEnabled)

typedef struct {
  FdtArgumentList *args;
  FdtDictionary* options;
} FdtArguments;

FdtArguments* fdt_arguments_new();
bool fdt_arguments_delete(FdtArguments*);

#ifdef __cplusplus

} /* extern "C" */

#endif

#endif
