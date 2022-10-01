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

#include <fdtools/plugins/fmt/cpm/cpm.h>

FdtCpmDirectory* fdt_cpm_format_ditectory_new(byte_t* data, size_t size)
{
  if (!data || size < FDT_CPM_DICTIONARY_SIZE)
    return NULL;
  return (FdtCpmDirectory*)data;
}

void fdt_cpm_format_ditectory_getfilename(FdtCpmDirectory* dir, char* filename)
{
  if (!dir)
    return;
  for (size_t n = 0; n < FDT_CPM_DICTIONARY_FILENAME_MAX; n++) {
    if (dir->Filename[n] == 0x20) {
      dir->Filename[n] = '\0';
    }
    filename[n] = dir->Filename[n];
  }
  filename[FDT_CPM_DICTIONARY_FILENAME_MAX] = '\0';
}
