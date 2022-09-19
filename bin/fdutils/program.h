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

#ifndef _FDTOOLS_COMMON_PROGRAM_H_
#define _FDTOOLS_COMMON_PROGRAM_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <fdtools/dev/device.h>
#include <fdtools/dev/image.h>
#include <fdtools/img/image.h>
#include <fdtools/plugins/image.h>
#include <fdtools/util/log.h>
#include <fdtools/util/program.h>
#include <fdtools/util/string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OPT_VERBOSE "v"
#define OPT_DEBUG "d"

#define OPT_CYLINDERS "c"
#define OPT_HEADS "h"
#define OPT_SECTORS "n"
#define OPT_SSIZE "s"
#define OPT_RETRY_PASSES "r"

#define ARG_IMAGE_FILENAME "<file name>"
#define ARG_IMAGE_DEVICE_FILENAME "<file or device name>"

void fdu_program_adddefaultoptions(FdtProgram* prg);
void fdu_program_adddeviceoptions(FdtProgram* prg);
bool fdu_program_parse_arguments(FdtProgram* prg, int argc, char* argv[], FdtError* err);
void fdu_program_usage(FdtProgram* prg, const char* args);

void panic(void);
void error(FdtError* err);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_COMMON_PROGRAM_H_ */
