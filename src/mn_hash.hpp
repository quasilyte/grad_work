#pragma once

#include <typedefs.hpp>
#include <dev_assert.hpp>

namespace mn_hash {
  const int MAX_HASHABLE_LEN = 9;
  const int NIL_HASH = 0;

  constexpr u64 encode1(u64 hash, char ch);
  constexpr u32 encode4(const char* cstr, u32 hash = 0);
  constexpr u64 encode9(const char* cstr, u64 hash = 0);

  inline u64 encode9(const char* bytes, u32 count);

  constexpr u64 operator "" _m9(const char* bytes, unsigned long count);
  constexpr u32 operator "" _m4(const char* bytes, unsigned long count);
}

constexpr u64 mn_hash::operator "" _m9(const char* bytes, unsigned long count) {
  dev_assert(count < 10);

  return mn_hash::encode9(bytes);
}

constexpr u32 mn_hash::operator "" _m4(const char* bytes, unsigned long count) {
  dev_assert(count < 5);

  return mn_hash::encode4(bytes);
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

inline u64 mn_hash::encode9(const char* bytes, u32 count) {
  dev_assert(count < 10);

  u64 hash = bytes[0];

  for (uint i = 1; i != count; ++i) {
    hash = encode1(hash, bytes[i]);
  }

  return hash;
}
