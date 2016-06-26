#include <lex/reader.hpp>

#include <mn_hash.hpp>
#include <err/lex_errors.hpp>

using namespace lex;
using namespace chars;
using dt::StrView;

Reader::Reader(): pos{nullptr}, pos_max{nullptr} {}

Reader::Reader(StrView input):
pos{input.Data()}, pos_max{input.Data() + input.Len()} {}

void Reader::DoSkip(uint n) {
  pos += n;
}

void Reader::DoSkip(Alphabet to_skip) {
  while (to_skip.Contains(*pos)) pos += 1;
}

void Reader::DoSkipUntil(char c) {
  while (CanRead() && c != *pos) pos += 1;
}

void Reader::DoSkipLiteral(char open_close) {
  char open = open_close;
  char close = open_close;

  if (TryConsume(open)) {
    while (CanRead()) {
      if (close == *pos && '\\' != PeekPrev()) {
        pos += 1;
        return;
      }
      pos += 1;
    }
  }

  // throw err::UnclosedLiteral{open_close};
}

template<class COMMENT>
void Reader::DoSkipGroup(char open, char close) {
  dev_assert(open != close);

  if (TryConsume(open)) {
    for (int depth = 0; CanRead(); pos += 1) {
      if (open == *pos) {
        depth += 1;
      } else if (close == *pos) {
        if (0 == depth) {
          pos += 1;
          return;
        } else {
          depth -= 1;
        }
      } else if ('"' == *pos) {
        DoSkipLiteral('"');
      } else {
        COMMENT::Skip(this);
      }
    }
  }

  // throw err::UnbalancedGroup{open, close};
}

StrView Reader::Read(Alphabet to_read) {
  const char* begin = pos;
  DoSkip(to_read);
  return StrView{begin, pos};
}

StrView Reader::ReadUntil(char c) {
  const char* begin = pos;
  DoSkipUntil(c);
  return StrView{begin, pos};
}

void Reader::DoSkipLine() {
  for (;;) {
    // Catching both '\0' and '\n' (but also '\t')
    while ('\n' < *pos) pos += 1;

    if (CanRead()) {
      if ('\n' == *pos) {
        pos += 1;
        return;
      } else {
        pos += 1; // Most likely (*pos == '\t')
      }
    } else {
      return;
    }
  }
}

StrView Reader::ReadLine() {
  const char* begin = pos;
  DoSkipLine();
  return StrView{begin, pos - 1};
}

StrView Reader::ReadLiteral(char open_close) {
  const char* begin = pos;
  DoSkipLiteral(open_close);
  return StrView{begin + 1, pos - 1};
}

template<class COMMENT>
StrView Reader::ReadGroup(char open, char close) {
  const char* begin = pos;
  DoSkipGroup<COMMENT>(open, close);
  return StrView{begin + 1, pos - 1};
}

template<class TAGGER>
Token Reader::ReadToken() {
  const char* begin = pos;
  u32 tag = TAGGER::Run(this);
  return Token{begin, static_cast<u32>(pos - begin), tag};
}

u64 Reader::ReadM9(Alphabet to_read) {
  const char* begin = pos;
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
    pos += 1; // Consuming
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

int Reader::TryConsume(Alphabet to_consume) {
  const char* begin = pos;
  DoSkip(to_consume);
  return pos - begin;
}

void Reader::MustConsume(char c) {
  if (!TryConsume(c)) {
    throw err::NoExpectedChar{c, *pos};
  }
}

void Reader::MustConsume(const char* cstr) {
  if (!TryConsume(cstr)) {
    // throw err::NoExpectedCstr{cstr};
  }
}

bool Reader::CanRead() const noexcept {
  return pos < pos_max;
}

const char* Reader::Pos() const noexcept {
  return pos;
}

#include <lex/c/comment.hpp>
#include <lex/num_tagger.hpp>

template void Reader::DoSkipGroup<c_lex::Comment>(char, char);
template StrView Reader::ReadGroup<c_lex::Comment>(char, char);
template Token Reader::ReadToken<NumTagger>();
