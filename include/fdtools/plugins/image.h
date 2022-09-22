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

#ifndef _FDTOOLS_PLUGIN_IMAGE_H_
#define _FDTOOLS_PLUGIN_IMAGE_H_

#include <fdtools/img/image.h>

#ifdef __cplusplus
extern "C" {
#endif

FDT_IMAGE_IMAGER fdt_image_plugins_getimager(const char*, FdtError*);
FdtImage* fdt_image_plugins_createimagebyfile(const char*, FdtError*);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_PLUGIN_IMAGE_H_ */
