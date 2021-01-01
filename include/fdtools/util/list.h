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

typedef bool (*FDT_LIST_DESTRUCTORFUNC)(void*);
typedef int (*FDT_LIST_COMPAREFUNC)(void*, void*);

#define FDT_LIST_STRUCT_MEMBERS \
  bool headFlag;                \
  struct _FdtList* prev;        \
  struct _FdtList* next;

typedef struct _FdtList {
  FDT_LIST_STRUCT_MEMBERS
} FdtList, FdtListNode;

void fdt_list_header_init(FdtList*);
void fdt_list_node_init(FdtListNode*);
bool fdt_list_insert(FdtList*, FdtList*);

FdtListNode* fdt_list_gets(FdtList*);
FdtListNode* fdt_list_get(FdtList*, int);
bool fdt_list_add(FdtList*, FdtListNode*);
size_t fdt_list_size(FdtList*);
bool fdt_list_move(FdtList*, FdtList*);
void fdt_list_clear(FdtList*, FDT_LIST_DESTRUCTORFUNC destructorFunc);

FdtListNode* fdt_list_prev_circular(FdtListNode*);
FdtListNode* fdt_list_prev(FdtListNode*);
FdtListNode* fdt_list_next_circular(FdtListNode*);
FdtListNode* fdt_list_next(FdtListNode*);
bool fdt_list_remove(FdtListNode*);

bool fdt_list_sort(FdtList* list, FDT_LIST_COMPAREFUNC comparefn);
bool fdt_list_issorted(FdtList* list, FDT_LIST_COMPAREFUNC comparefn);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _FDTOOLS_UTIL_LIST_H_ */
