#pragma once

#include <string.h>

#include "vec.h"

typedef struct Str Str;
struct Str {
  CharVec chars;
};

static inline Str str_new(size_t len);
static inline Str str_from_cstr(char* cstr);
static inline void str_free(Str* self);

static inline const char* str_chars(const Str* self);
static inline char* str_chars_mut(const Str* self);

static inline size_t str_len(const Str* self);
static inline char str_char_at(const Str* self, size_t pos);

static inline void str_push_char(Str* self, char ch);
static inline void str_push_cstr(Str* self, char* cstr);

static inline void str_set_char(Str* self, char ch, size_t pos);

/* Inline functions implementstion */

static inline Str str_new(size_t len) {
  return (Str) {
    .chars = vecc_new(len + 1)
  };
}

static inline Str str_from_cstr(char* cstr) {
  size_t len = strlen(cstr);
  CharVec chars = vecc_new(len + 1);
  vec_npush(&chars, cstr, len);

  return (Str) {
    .chars = chars
  };
}

static inline const char* str_chars(const Str* self) {
  return self->chars.arr.mem;
}

static inline char* str_chars_mut(const Str* self) {
  return self->chars.arr.mem;
}

static inline size_t str_len(const Str* self) {
  return self->chars.len;
}


static inline char str_char_at(const Str* self, size_t pos) {
  return self->chars.arr.mem[pos];
}

static inline void str_push_char(Str* self, char ch) {
  vec_push(&self->chars, ch);
}

static inline void str_push_cstr(Str* self, char* cstr) {
  vec_npush(&self->chars, cstr, strlen(cstr));
}

static inline void str_set_char(Str* self, char ch, size_t pos) {
  self->chars.arr.mem[pos] = ch;
}

static inline void str_free(Str* self) {
  vec_free(&self->chars);
}
