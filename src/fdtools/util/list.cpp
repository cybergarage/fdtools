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

FdtList* fdt_list_new();
bool fdt_list_delete(FdtList*);
FdtListNode* fdt_list_getminnode(FdtList*, FDT_LIST_COMPAREFUNC);

FdtList* fdt_list_new()
{
  FdtList* list = (FdtList*)malloc(sizeof(FdtList));
  if (!list)
    return NULL;
  fdt_list_header_init(list);
  return list;
}

bool fdt_list_delete(FdtList* list)
{
  if (!list)
    return false;
  free(list);
  return true;
}

void fdt_list_header_init(FdtList* list)
{
  if (!list)
    return;

  list->headFlag = true;
  list->prev = list->next = list;
}

void fdt_list_node_init(FdtListNode* node)
{
  if (!node)
    return;

  node->headFlag = false;
  node->prev = node->next = node;
}

size_t fdt_list_size(FdtList* list)
{
  if (!list)
    return 0;

  size_t list_cnt = 0;
  for (FdtList* node = fdt_list_next(list); node; node = fdt_list_next(node))
    list_cnt++;

  return list_cnt;
}

FdtListNode* fdt_list_gets(FdtList* list) { return fdt_list_next(list); }

FdtListNode* fdt_list_get(FdtList* list, int index)
{
  if (!list)
    return NULL;

  FdtList* node = fdt_list_next(list);
  for (int n = 0; n < index; n++) {
    if (!node)
      break;
    node = fdt_list_next(node);
  }

  return node;
}

bool fdt_list_insert(
    FdtList* plist,
    FdtList* list)
{
  if ((!plist) || (!list))
    return false;

  list->prev = plist;
  list->next = plist->next;
  plist->next->prev = list;
  plist->next = list;

  return true;
}

bool fdt_list_add(
    FdtList* list,
    FdtList* node)
{
  if ((!list) || (!node))
    return false;

  if (!list->prev)
    return false;

  return fdt_list_insert(list->prev, node);
}

bool fdt_list_move(FdtList* from, FdtList* to)
{
  FdtList* node = fdt_list_gets(from);
  while (node) {
    if (!fdt_list_remove(node))
      return false;
    if (!fdt_list_add(to, node))
      return false;
    node = fdt_list_gets(from);
  }
  return true;
}

bool fdt_list_remove(FdtListNode* node)
{
  if (!node)
    return false;

  if ((!node->prev) || (!node->next))
    return false;

  node->prev->next = node->next;
  node->next->prev = node->prev;
  node->prev = node->next = node;

  return true;
}

FdtListNode* fdt_node_prev_circular(
    FdtListNode* node)
{
  if (!node)
    return NULL;

  if (!node->prev)
    return NULL;

  if (node->prev->headFlag)
    node = node->prev;

  return node->prev;
}

FdtListNode* fdt_node_prev(
    FdtListNode* node)
{
  if (!node)
    return NULL;

  if (!node->prev)
    return NULL;

  if (node->prev->headFlag == true)
    return NULL;

  return node->prev;
}

FdtListNode* fdt_node_next_circular(
    FdtListNode* node)
{
  if (!node)
    return NULL;

  if (!node->next)
    return NULL;

  if (node->next->headFlag == true)
    node = node->next;

  return node->next;
}

FdtListNode* fdt_list_next(
    FdtListNode* node)
{
  if (!node)
    return NULL;

  if (!node->next)
    return NULL;

  if (node->next->headFlag == true)
    return NULL;

  return node->next;
}

FdtListNode* fdt_list_getminnode(FdtList* list, FDT_LIST_COMPAREFUNC comparefn)
{
  if (!list || !comparefn)
    return NULL;

  FdtListNode* min_node = fdt_list_gets(list);
  if (!min_node)
    return NULL;

  FdtListNode* node = fdt_list_next(min_node);
  while (node) {
    if (comparefn(node, min_node) < 0) {
      min_node = node;
    }
    node = fdt_list_next(node);
  }

  return min_node;
}

bool fdt_list_sort(FdtList* list, FDT_LIST_COMPAREFUNC comparefn)
{
  if (!list || !comparefn)
    return false;

  FdtList* tmp_list = fdt_list_new();
  if (!tmp_list)
    return false;

  fdt_list_move(list, tmp_list);
  FdtListNode* min_node = fdt_list_getminnode(tmp_list, comparefn);
  while (min_node) {
    fdt_list_remove(min_node);
    fdt_list_add(list, min_node);
    min_node = fdt_list_getminnode(tmp_list, comparefn);
  }

  fdt_list_delete(tmp_list);

  return true;
}

bool fdt_list_issorted(FdtList* list, FDT_LIST_COMPAREFUNC comparefn)
{
  if (!list || !comparefn)
    return false;

  FdtListNode* prev_node = fdt_list_gets(list);
  if (!prev_node)
    return true;

  FdtListNode* node = fdt_list_next(prev_node);
  while (node) {
    if (0 < comparefn(prev_node, node))
      return false;
    prev_node = node;
    node = fdt_list_next(node);
  }

  return true;
}

void fdt_list_clear(FdtList* list, FDT_LIST_DESTRUCTORFUNC destructorFunc)
{
  if (!list)
    return;

  FdtList* node = fdt_list_next(list);
  while (node) {
    FdtList* next_node = fdt_list_next(node);
    fdt_list_remove(node);
    if (destructorFunc) {
      destructorFunc(node);
    }
    else {
      free(node);
    }
    node = next_node;
  }
}
