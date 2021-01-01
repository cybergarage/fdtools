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

#include <boost/test/unit_test.hpp>

#include <fdtools/util/list.h>

typedef struct {
  FDT_LIST_STRUCT_MEMBERS
  int value;
} TestList, TestNode;

TestList* test_list_new()
{
  TestList* list = (TestList*)calloc(sizeof(TestList), 1);
  fdt_list_header_init((FdtList*)list);
  return list;
}

TestNode* test_node_new(int value)
{
  TestNode* node = (TestNode*)calloc(sizeof(TestNode), 1);
  if (!node) {
    return NULL;
  }
  fdt_list_node_init((FdtListNode*)node);
  node->value = value;
  return node;
}

int test_node_compare(TestNode* t, TestNode* o)
{
  if (t->value == o->value)
    return 0;
  if (t->value < o->value)
    return -1;
  return 1;
}

bool fdt_test_node_delete(TestList* node)
{
  fdt_list_remove((FdtListNode*)node);
  free(node);
  return true;
}

bool test_list_delete(TestList* list)
{
  free(list);
  return true;
}

BOOST_AUTO_TEST_CASE(ListSortTest)
{
  TestList* list = test_list_new();
  BOOST_CHECK(test_list_delete(list));
}
