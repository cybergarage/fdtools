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

#include <fdtools/fmt/file.h>

FdtFile* fdt_file_new()
{
  FdtFile* file = (FdtFile*)calloc(sizeof(FdtFile), 1);
  if (!file) {
    return NULL;
  }

  fdt_list_node_init((FdtListNode*)file);
  file->name = fdt_string_new();
  file->data = NULL;
  file->data_size = 0;

  return file;
}

bool fdt_file_delete(FdtFile* file)
{
  if (!file)
    return false;

  fdt_string_delete(file->name);

  free(file);

  return true;
}

bool fdt_file_setdata(FdtFile* file, byte_t* data, size_t data_size)
{
  if (!file)
    return false;

  if (file->data) {
    free(file->data);
    file->data_size = 0;
  }

  file->data = (byte_t*)malloc(data_size);
  if (!file->data)
    return false;

  memcpy(file->data, data, data_size);
  file->data_size = data_size;

  return true;
}
