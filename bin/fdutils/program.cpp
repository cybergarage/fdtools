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

#include "program.h"
#include "console.h"

bool program_verbose_enabled = false;
bool program_debug_enabled = false;

void fdu_program_add_default_options(FdtProgram* prg)
{
  fdt_program_addoption(prg, OPT_VERBOSE, "enable verbose messages", false, "");
  fdt_program_addoption(prg, OPT_DEBUG, "enable debug messages", false, "");
}

void fdu_program_usage(FdtProgram* prg, const char* args)
{
  fdu_console_flush();
  printf("Usage: %s [OPTIONS] %s\n", fdt_program_getname(prg), args);
  fdt_program_printoptionusages(prg);
}

bool fdu_program_parse_arguments(FdtProgram* prg, int argc, char* argv[], FdtError* err)
{
  if (!fdt_program_parse(prg, argc, argv, err)) {
    return false;
  }

  // Sets command line options

  if (fdt_program_isoptionenabled(prg, OPT_VERBOSE)) {
    program_verbose_enabled = true;
  }
  if (fdt_program_isoptionenabled(prg, OPT_DEBUG)) {
    program_debug_enabled = true;
    fdt_log_setlevel(FDT_LOG_DEBUG);
  }

  return true;
}

void fdu_console_error(FdtError* err)
{
  fdu_console_flush();

  printf("%s\n", program_debug_enabled ? fdt_error_getdebugmessage(err) : fdt_error_getmessage(err));
  fflush(stdout);
}

void exit_error(FdtError* err)
{
  fdu_console_error(err);
  exit(EXIT_FAILURE);
}

void panic(void)
{
  exit(EXIT_FAILURE);
}
