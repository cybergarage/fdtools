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

#ifndef _FDTOOLS_FMT_FILE_H_
#define _FDTOOLS_FMT_FILE_H_

#include <stdio.h>

#include <fdtools/error.h>
#include <fdtools/typedef.h>
#include <fdtools/util/list.h>
#include <fdtools/util/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  FDT_LIST_STRUCT_MEMBERS
  FdtString* name;
  byte_t* data;
  size_t data_size;
} FdtFile, FdtFiles;

////////////////////////////////////////
// fdt_file_*
////////////////////////////////////////

FdtFile* fdt_file_new();
bool fdt_file_delete(FdtFile*);

bool fdt_file_setdata(FdtFile* file, byte_t* data, size_t data_size);

#define fdt_file_setname(file, name) fdt_string_setvalue(file->name, name)
#define fdt_file_getname(file) fdt_string_getvalue(file->name)

#define fdt_file_getdatasize(file) (file->data_size)

////////////////////////////////////////
// fdt_files_*
////////////////////////////////////////

FdtFiles* fdt_files_new();
void fdt_files_delete(FdtFiles*);

#define fdt_files_size(files) fdt_list_size((FdtList*)files)
#define fdt_files_gets(files) (FdtFile*)fdt_list_gets((FdtList*)files)
#define fdt_files_addfile(files, file) fdt_list_add((FdtList*)files, (FdtListNode*)file)
#define fdt_files_clear(files) fdt_list_clear((FdtList*)files, (FDT_LIST_DESTRUCTORFUNC)fdt_file_delete)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_FMT_FILE_H_ */
