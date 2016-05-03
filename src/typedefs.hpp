#pragma once

#include <cstdint>
#include <cstddef>

typedef size_t usize;
typedef unsigned int uint;

typedef int64_t i64;
typedef int32_t i32;
typedef uint8_t i8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef int8_t u8;

typedef double f64;
typedef float f32;

typedef f64 real;
typedef i64 integer;

inline real operator "" _r(long double literal_value) {
  return static_cast<real>(literal_value);
}

inline integer operator "" _i(unsigned long long literal_value) {
  return static_cast<integer>(literal_value);
}
