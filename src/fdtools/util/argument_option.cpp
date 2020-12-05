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

#include <fdtools/util/program.h>

FdtArgumentOption* fdt_argument_option_new()
{
  FdtArgumentOption* opt = (FdtArgumentOption*)malloc(sizeof(FdtArgumentOption));
  if (!opt) {
    return NULL;
  }

  opt->name = fdt_string_new();
  opt->value = fdt_string_new();
  fdt_argument_option_setenabled(opt, false);
  fdt_argument_option_setvalueenabled(opt, false);

  if (!opt->name || !opt->value) {
    fdt_argument_option_delete(opt);
    return NULL;
  }

  return opt;
}

bool fdt_argument_option_delete(FdtArgumentOption* opt)
{
  if (!opt)
    return true;
  fdt_string_delete(opt->name);
  fdt_string_delete(opt->value);
  free(opt);
  return true;
}
