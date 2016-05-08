#pragma once

#include "typedefs.hpp"

namespace djb2_hash {
  inline u64 encode(const char* cstr);
  inline u64 encode(const char* bytes, u32 count);
}

inline u64 djb2_hash::encode(const char* cstr) {
  usize hash = static_cast<u64>(5381);

  for (auto p = cstr; *p; ++p) {
    hash = ((hash << 5) + hash) + *p;
  }

  return hash;
}

inline u64 djb2_hash::encode(const char* bytes, u32 count) {
  u64 hash = static_cast<u64>(5381);

  for (uint i = 0; i < count; ++i) {
    hash = ((hash << 5) + hash) + bytes[i];
  }

  return hash;
}
