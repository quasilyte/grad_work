#pragma once

#include "typedefs.hpp"

namespace mn_hash {
  const int MAX_HASHABLE_LEN = 9;
  const int NIL_HASH = 0;

  constexpr u64 encode1(u64 hash, char ch);
  constexpr u32 encode4(const char *cstr, u32 hash = 0);
  constexpr u64 encode9(const char *cstr, u64 hash = 0);

  inline u64 encode9(const char *cstr, u32 len);
}

constexpr u64 mn_hash::encode1(u64 hash, char ch) {
  const int BITS_PER_ASCII = 7;
  return (hash << BITS_PER_ASCII) + ch;
}

constexpr u32 mn_hash::encode4(const char *cstr, u32 hash) {
  return *cstr ? encode4(cstr + 1, encode1(hash, *cstr)) : hash;
}

constexpr u64 mn_hash::encode9(const char *cstr, u64 hash) {
  return *cstr ? encode9(cstr + 1, encode1(hash, *cstr)) : hash;
}

inline u64 mn_hash::encode9(const char *cstr, u32 len) {
  u64 hash = cstr[0];

  for (uint i = 1; i != len; ++i) {
    hash = encode1(hash, cstr[i]);
  }

  return hash;
}
