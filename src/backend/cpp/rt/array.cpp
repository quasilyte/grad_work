#include "array.hpp"

#include <cassert>

std::vector<Array_> Arrays_::int_arrays{1};

ArrayHandle_::ArrayHandle_(Int_ id): id{id} {
  puts("dtor");
}

ArrayHandle_::ArrayHandle_(ArrayHandle_&& other) {
  puts("move");
}

ArrayHandle_::~ArrayHandle_() {
  auto mem = Arrays_::int_arrays[id].elems;
  assert(nullptr != mem);
  delete mem;
  Arrays_::int_arrays[id].elems = nullptr;
}


