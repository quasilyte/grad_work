#pragma once

#include "core.hpp"

#include <vector>
#include <cstdio>

struct ArrayHandle_ {
  Int_ id;

  ArrayHandle_(Int_ id);
  ArrayHandle_(ArrayHandle_&&);
  // ArrayHandle_(const ArrayHandle_&);
  ~ArrayHandle_();
};

struct Array_ {
  Int_ len;
  Int_* elems = nullptr;
};

struct Arrays_ {
  static ArrayHandle_ New(Int_ len) {
    for (std::size_t i = 0; i < int_arrays.size(); ++i) {
      auto& arr = int_arrays[i];

      if (nullptr == arr.elems) {
        arr.elems = new Int_[len];
        arr.len = len;
        return ArrayHandle_{static_cast<Int_>(i)};
      }
    }

    throw "no more slots";
  }

  static std::vector<Array_> int_arrays;
};

inline Int_ len_(const ArrayHandle_& arr) {
  return Arrays_::int_arrays[arr.id].len;
}

inline Int_ nth_(const ArrayHandle_& arr, Int_ idx) {
  return Arrays_::int_arrays[arr.id].elems[idx];
}

inline void set_(const ArrayHandle_& arr, Int_ idx, Int_ val) {
  Arrays_::int_arrays[arr.id].elems[idx] = val;
}
