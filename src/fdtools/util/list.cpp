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

#include <fdtools/util/list.h>

void fdt_list_header_init(FdtList* list)
{
  if (!list)
    return;

  list->headFlag = true;
  list->prev = list->next = list;
}

void fdt_list_node_init(FdtList* list)
{
  if (!list)
    return;

  list->headFlag = false;
  list->prev = list->next = list;
}

size_t fdt_list_size(FdtList* headList)
{
  if (!headList)
    return 0;

  size_t listCnt = 0;
  for (FdtList* list = fdt_list_next(headList); list; list = fdt_list_next(list))
    listCnt++;

  return listCnt;
}

FdtList* fdt_list_get(FdtList* headList, int index)
{
  if (!headList)
    return NULL;

  FdtList* list = fdt_list_next(headList);
  for (int n = 0; n < index; n++) {
    if (!list)
      break;
    list = fdt_list_next(list);
  }

  return list;
}

void fdt_list_insert(
    FdtList* prevList,
    FdtList* list)
{
  if ((!prevList) || (!list))
    return;

  list->prev = prevList;
  list->next = prevList->next;
  prevList->next->prev = list;
  prevList->next = list;
}

void fdt_list_add(
    FdtList* headList,
    FdtList* list)
{
  if ((!headList) || (!list))
    return;

  if (!headList->prev)
    return;

  fdt_list_insert(headList->prev, list);
}

void fdt_list_remove(FdtList* list)
{
  if (!list)
    return;

  if ((!list->prev) || (!list->next))
    return;

  list->prev->next = list->next;
  list->next->prev = list->prev;
  list->prev = list->next = list;
}

FdtList* fdt_list_prev_circular(
    FdtList* list)
{
  if (!list)
    return NULL;

  if (!list->prev)
    return NULL;

  if (list->prev->headFlag)
    list = list->prev;

  return list->prev;
}

FdtList* fdt_list_prev(
    FdtList* list)
{
  if (!list)
    return NULL;

  if (!list->prev)
    return NULL;

  if (list->prev->headFlag == true)
    return NULL;

  return list->prev;
}

FdtList* fdt_list_next_circular(
    FdtList* list)
{
  if (!list)
    return NULL;

  if (!list->next)
    return NULL;

  if (list->next->headFlag == true)
    list = list->next;

  return list->next;
}

FdtList* fdt_list_next(
    FdtList* list)
{
  if (!list)
    return NULL;

  if (!list->next)
    return NULL;

  if (list->next->headFlag == true)
    return NULL;

  return list->next;
}

void fdt_list_clear(FdtList* headList, FDT_LIST_DESTRUCTORFUNC destructorFunc)
{
  if (!headList)
    return;

  FdtList* list = fdt_list_next(headList);
  while (list) {
    FdtList* nextList = fdt_list_next(list);
    fdt_list_remove(list);
    if (destructorFunc) {
      destructorFunc(list);
    }
    else {
      free(list);
    }
    list = nextList;
  }
}
