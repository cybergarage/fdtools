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

bool test_node_delete(TestList* node)
{
  fdt_list_remove((FdtListNode*)node);
  free(node);
  return true;
}

TestList* test_list_new()
{
  TestList* list = (TestList*)calloc(sizeof(TestList), 1);
  fdt_list_header_init((FdtList*)list);
  return list;
}

bool test_list_addnode(TestList* list, TestNode* node)
{
  return fdt_list_add((FdtList*)list, (FdtListNode*)node);
}

bool test_list_clear(TestList* list)
{
  fdt_list_clear((FdtList*)list, (FDT_LIST_DESTRUCTORFUNC)test_node_delete);
  return true;
}

bool test_list_delete(TestList* list)
{
  test_list_clear(list);
  free(list);
  return true;
}

size_t test_list_size(TestList* list)
{
  return fdt_list_size((FdtList*)list);
}

BOOST_AUTO_TEST_CASE(ListSort)
{
  TestList* list = test_list_new();
  BOOST_REQUIRE(list);

  BOOST_REQUIRE(test_list_addnode(list, test_node_new(3)));
  BOOST_REQUIRE(test_list_addnode(list, test_node_new(2)));
  BOOST_REQUIRE(test_list_addnode(list, test_node_new(1)));
  BOOST_REQUIRE(!fdt_list_issorted((FdtList*)list, (FDT_LIST_COMPAREFUNC)test_node_compare));
  BOOST_REQUIRE_EQUAL(test_list_size(list), 3);

  BOOST_CHECK(fdt_list_sort((FdtList*)list, (FDT_LIST_COMPAREFUNC)test_node_compare));
  BOOST_CHECK(fdt_list_issorted((FdtList*)list, (FDT_LIST_COMPAREFUNC)test_node_compare));
  BOOST_REQUIRE_EQUAL(test_list_size(list), 3);

  BOOST_CHECK(test_list_delete(list));
}
