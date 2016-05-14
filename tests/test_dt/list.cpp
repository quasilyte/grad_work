#include "test_dt/suit.hpp"

#include "dt/alist.hpp"
#include "dt/hlist.hpp"
#include "test_utils.hpp"

using namespace dt;

template<template<class> class T> void test_list() {
  const i32 value1 = 10;
  const i32 value2 = 12;
  const i32 nil_value{};
  StrView key1{"foo"};
  StrView key2{"var"};
  T<i32> list;

  list.Insert(key2, 25);
  list.Insert(key1, value1);
  TRUE(list.Size() == 2);
  TRUE(list.Find(key1) == value1);

  list.Insert(key1, value2);
  TRUE(list.Find(key1) == value2);
  TRUE(list.Find(key2, 3) == 25);
  FALSE(list.Find(key2, 1) == 25);
  FALSE(list.Find(key2, 2) == 25);

  list.Drop(1);
  TRUE(list.Find(key1) == value1);

  list.Drop(1);
  TRUE(list.Find(key1) == nil_value);
  TRUE(list.Size() == 1);
}

template void test_list<Alist>();
template void test_list<Hlist>();
