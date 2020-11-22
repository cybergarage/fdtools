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

#ifndef _FDTOOLS_UTIL_LIST_H_
#define _FDTOOLS_UTIL_LIST_H_

#include <fdtools/typedef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*FDT_LIST_DESTRUCTORFUNC)(void*);

#define FDT_LIST_STRUCT_MEMBERS \
  bool headFlag;                \
  struct _FdtList* prev;        \
  struct _FdtList* next;

typedef struct _FdtList {
  FDT_LIST_STRUCT_MEMBERS
} FdtList;

void fdt_list_header_init(FdtList* list);
void fdt_list_node_init(FdtList* list);
void fdt_list_insert(FdtList* prevList, FdtList* list);
void fdt_list_add(FdtList* headList, FdtList* list);
void fdt_list_remove(FdtList* list);
size_t fdt_list_size(FdtList* headList);
FdtList* fdt_list_get(FdtList* headList, int index);
FdtList* fdt_list_prev_circular(FdtList* list);
FdtList* fdt_list_prev(FdtList* list);
FdtList* fdt_list_next_circular(FdtList* list);
FdtList* fdt_list_next(FdtList* list);
void fdt_list_clear(FdtList* headList, FDT_LIST_DESTRUCTORFUNC destructorFunc);

FdtList* fdt_list_gets(FdtList* headList) { return fdt_list_next(headList); }

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _FDTOOLS_UTIL_LIST_H_ */
