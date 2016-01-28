#pragma once

#include <cstdio>

const int MAX_HASHABLE_LEN = 9;
const int NIL_HASH = 0;

#define BITS_PER_ASCII 7

inline constexpr u64 m_encode(u64 hash, char ch) {
  return (hash << BITS_PER_ASCII) + ch;
}

inline constexpr u32 m4_hash(const char *cstr, u32 hash = 0) {
  return *cstr ? m4_hash(cstr + 1, m_encode(hash, *cstr)) : hash;
}

inline constexpr u64 m9_hash(const char *cstr, u64 hash = 0) {
  return *cstr ? m9_hash(cstr + 1, m_encode(hash, *cstr)) : hash;
}

inline u64 m9_hash(const char *cstr, int len) {
  u64 hash = cstr[0];
  for (int i = 1; i != len; ++i) {
    hash = m_encode(hash, cstr[i]);
  }
  return hash;
}

#undef BITS_PER_ASCII
