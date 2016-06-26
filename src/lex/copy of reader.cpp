#include <lex/reader.hpp>

#include <mn_hash.hpp>

using namespace lex;
using namespace chars;
using dt::StrView;

/*
 * Public:
 */

Reader::Reader():
pos{nullptr}, pos_max{nullptr} {}

Reader::Reader(StrView input):
pos{input.Data()}, pos_max{input.Data() + input.Len()} {}

void Reader::Skip(Alphabet to_skip) {
  while (to_skip.Contains(*pos)) pos += 1;
}

void Reader::Skip(uint n) {
  pos += n;
}

void Reader::SkipUntil(char c) {
  while (c != *pos) pos += 1;
}

StrView Reader::Read(Alphabet to_read) {
  Skip(SPACES);

  return StrView{pos, PosAfter(to_read)};
}

StrView Reader::ReadUntil(char c) {
  Skip(SPACES);

  return StrView{pos, PosAfter(c)};
}

StrView Reader::ReadGroup(char open_close) {
  return ReadGroup(open_close, open_close);
}

StrView Reader::ReadGroup(char open, char close) {
  Skip(SPACES);

  if (TryConsume(open)) {
    const char* begin = pos;

    while (CanRead()) {
      if (close == *pos && '\\' != PeekPrev()) {
        return StrView{begin, pos++};
      }

      pos += 1;
    }
  }

  return StrView{};
}

StrView Reader::ReadBalancedGroup(char open, char close) {
  dev_assert(open != close);

  Skip(SPACES);

  if (TryConsume(open)) {
    const char* begin = pos;

    for (int depth = 0; CanRead(); pos += 1) {
      if (open == *pos) {
        depth += 1;
      } else if (close == *pos) {
        if (0 == depth) {
          return StrView{begin, pos++};
        } else {
          depth -= 1;
        }
      }
    }
  }

  return StrView{};
}

u64 Reader::ReadM9(Alphabet to_read) {
  const char* begin = PosAfter(SPACES);
  u64 hash = 0;

  while (to_read.Contains(*pos)) {
    hash = mn_hash::encode1(hash, *pos);
    pos += 1;
  }

  // 0 is invalid m9 hash
  return (pos - begin) < 10 ? hash : 0;
}

char Reader::PeekCurrent() const noexcept {
  return *pos;
}

char Reader::PeekNext() const noexcept {
  return *(pos + 1);
}

char Reader::PeekPrev() const noexcept {
  return *(pos - 1);
}

bool Reader::TryConsume(char c) {
  if (c == *pos) {
    pos += 1; // Consuming.
    return true;
  } else {
    return false;
  }
}

bool Reader::TryConsume(const char* cstr) {
  const char* p = pos;

  while (*p == *cstr) {
    p += 1;
    cstr += 1;
  }

  if (*cstr) {
    // `cstr` should be null terminated,
    // therefore if we are not reached \0 matching is failed
    return false;
  } else {
    pos = p; // Position after match
    return true;
  }
}

bool Reader::CanRead() const noexcept {
  return pos < pos_max;
}

/*
 * Private:
 */

const char* Reader::PosAfter(Alphabet to_skip) {
  Skip(to_skip);

  return pos;
}

const char* Reader::PosAfter(char c) {
  SkipUntil(c);

  return pos;
}
