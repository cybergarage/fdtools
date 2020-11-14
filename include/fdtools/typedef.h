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

#ifndef _FDTOOLS_TYPEDEF_H_
#define _FDTOOLS_TYPEDEF_H_

#include <stdlib.h>

#if defined(__APPLE_CPP__) || defined(__APPLE_CC__)
#include <TargetConditionals.h>
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#if defined(__APPLE_CPP__) || defined(__APPLE_CC__) || defined(WIN32)
#define HAVE_SNPRINTF 1
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if (__STDC_VERSION__ >= 199901L) || defined(HAVE_STDBOOL_H)
#include <stdbool.h>
#else
#if !defined(bool)
#define bool int
#endif
#if !defined(true)
#define true 1
#endif
#if !defined(false)
#define false 0
#endif
#endif

#if !defined(byte)
typedef unsigned int byte;
#endif

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_TYPEDEF_H_ */
