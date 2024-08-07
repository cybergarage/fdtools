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

#include <fdtools/fmt/file.h>

FdtFiles* fdt_files_new()
{
  FdtFiles* files = (FdtFiles*)malloc(sizeof(FdtFiles));
  if (!files) {
    return NULL;
  }

  fdt_list_header_init((FdtList*)files);

  return files;
}

void fdt_files_delete(FdtFiles* files)
{
  fdt_files_clear(files);
  free(files);
}
