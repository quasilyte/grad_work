#include <lex/cursor.hpp>

#include <mn_hash.hpp>
#include <errors.hpp>
#include <unit/source.hpp>
#include <deps/c/string.hpp>

using namespace lex;

dt::StrView slice(const char* begin, const char* end) {
  return dt::StrView{begin, static_cast<u32>(end - begin)};
}

Cursor* lex::skip(Cursor* cur, const int* to_skip) {
  while (to_skip[static_cast<int>(*cur->pos)]) {
    cur->pos += 1;
  }

  return cur;
}

Cursor* lex::skip(Cursor* cur, int n) {
  cur->pos += n;

  return cur;
}

Cursor* lex::skip_until(Cursor* cur, char target) {
  while (*cur->pos != target) {
    cur->pos += 1;
  }

  if (*cur->pos == target) { // Found {target}
    return cur;
  } else {
    // If we not found {target}, this is exceptional situation
    throw err::SkipUntilFailure{target};
  }
}

dt::StrView lex::read(Cursor* cur, const int *to_read) {
  const char* begin = cur->pos;

  while (to_read[static_cast<int>(*cur->pos)]) {
    cur->pos += 1;
  }

  return slice(begin, cur->pos);
}

dt::StrView lex::read(Cursor* cur, void(*scan)(Cursor*)) {
  const char* begin = cur->pos;
  scan(cur);

  return slice(begin, cur->pos);
}

dt::StrView lex::read_until(Cursor* cur, char target) {
  const char* begin = cur->pos;
  skip_until(cur, target);

  return slice(begin, cur->pos);
}

char lex::read_next(Cursor* cur) {
  return *cur->pos++;
}

lex::Token lex::read_token(Cursor* cur, u32(*tokenize)(Cursor*)) {
  const char* begin = cur->pos;
  u32 tag = tokenize(cur);

  return lex::Token{begin, static_cast<u32>(cur->pos - begin), tag};
}

dt::StrView lex::read_group(Cursor* cur, char open_close) {
  if (open_close == *cur->pos) {
    const char* begin = cur->pos;

    cur->pos += 1;

    while (open_close != *cur->pos) {
      cur->pos += 1;
    }

    cur->pos += 1;
    return slice(begin, cur->pos);
  }

  return dt::StrView{};
}

dt::StrView lex::read_group(Cursor* cur, char open, char close) {
  const char* begin = cur->pos;
  cur->pos += 1;
  int depth = 0;

  while (can_read(cur)) {
    if (open == *cur->pos) {
      depth += 1;
    } else if (close == *cur->pos) {
      if (depth == 0) {
        cur->pos += 1;
        return slice(begin, cur->pos);
      } else {
        depth -= 1;
      }
    }

    cur->pos += 1;
  }

  throw "ReadGroup: unbalanced group";
}

u64 lex::read_m9(Cursor* cur, const int *to_read) {
  const char* begin = cur->pos;
  u64 hash = 0;

  while (to_read[static_cast<int>(*cur->pos)]) {
    hash = mn_hash::encode1(hash, *cur->pos);
    cur->pos += 1;
  }

  // 0 is invalid m9 hash
  return (cur->pos - begin) < 10 ? hash : 0;
}

char lex::at(const Cursor* cur) {
  return *cur->pos;
}

char lex::peek(const Cursor* cur) {
  return *(cur->pos + 1);
}

bool lex::can_read(const Cursor* cur) {
  return cur->pos < cur->pos_max;
}

bool lex::try_consume(Cursor* cur, char to_consume) {
  if (*cur->pos == to_consume) {
    cur->pos += 1; // Consumed
    return true;
  } else {
    return false;
  }
}

bool lex::try_consume(Cursor* cur, const char* to_consume) {
  const char* p = cur->pos;

  while (*p == *to_consume) {
    p += 1;
    to_consume += 1;
  }

  if (*to_consume) { // Not fully matched
    return false;
  } else {
    cur->pos = p; // Position after match
    return true;
  }
}

int lex::try_consume(Cursor* cur, const int *to_consume) {
  const char* begin = cur->pos;
  skip(cur, to_consume);

  return cur->pos - begin;
}

int lex::line_number(const Cursor* cur) {
  return unit::get_line_number(cur->pos);
}

Cursor::Cursor(dt::StrView input):
pos{input.Data()}, pos_max{input.Data() + input.Len()} {}
