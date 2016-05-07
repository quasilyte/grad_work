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

static_assert(
  sizeof(i64) == 8 &&
  sizeof(i32) == 4 &&
  sizeof(i8) == 1 &&
  sizeof(u64) == 8 &&
  sizeof(u32) == 4 &&
  sizeof(u8) == 1 &&
  sizeof(f64) == 8 &&
  sizeof(f32) == 4,
  "type size expectations failed"
);
