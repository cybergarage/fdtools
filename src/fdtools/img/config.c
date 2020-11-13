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

#include <fdtools/img/config.h>

FdtImageConfig* fdt_image_config_new()
{
  FdtImageConfig* config;

  config = (FdtImageConfig*)malloc(sizeof(FdtImageConfig));
  if (!config) {
    return NULL;
  }

  return config;
}

void fdt_image_config_delete(FdtImageConfig* config)
{
  free(config);
}
