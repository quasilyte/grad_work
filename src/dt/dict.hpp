#pragma once

#include "typedefs.hpp"
#include "dt/str_view.hpp"
#include "djb2_hash.hpp"
#include <unordered_map>

namespace dt {
  template<class T> class Dict;
}

template<class T> class dt::Dict {
public:
  void Put(const char* key, T value);
  void Put(const char* key, u32 key_len, T value);
  void Put(StrView key, T value);

  T& Get(const char* key);
  T& Get(const char* key, u32 key_len);
  T& Get(StrView key);

private:
  std::unordered_map<StrView, T> bag;
};

template<> struct std::hash<dt::StrView> {
  usize operator()(const dt::StrView& key) const {
    return djb2_hash::encode(key.Data(), key.Len());
  }
};
