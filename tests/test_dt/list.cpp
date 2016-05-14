#include "test_dt/suit.hpp"

#include "dt/alist.hpp"
#include "dt/hlist.hpp"
#include "test_utils.hpp"

using namespace dt;

template<template<class> class T> void test_list() {
  const i32 value1 = 10;
  const i32 value2 = 12;
  const i32 nil_value{};
  StrView key{"foo"};
  T<i32> list;

  list.Insert("bar", 25);
  list.Insert(key, value1);
  TRUE(list.Size() == 2);
  TRUE(list.Find(key) == value1);

  list.Insert(key, value2);
  TRUE(list.Find(key) == value2);

  list.Drop(1);
  TRUE(list.Find(key) == value1);

  list.Drop(1);
  TRUE(list.Find(key) == nil_value);
  TRUE(list.Size() == 1);
}

template void test_list<Alist>();
template void test_list<Hlist>();
