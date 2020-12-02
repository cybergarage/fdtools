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

#include <stdbool.h>
#include <stdint.h>
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

#if defined(__GNUC__) || defined(__clang__)
#define FDT_ATTR_PACKED __attribute__((packed))
#endif

#if !defined(byte_t)
typedef uint8_t byte_t;
#endif

#endif /* _FDTOOLS_TYPEDEF_H_ */
