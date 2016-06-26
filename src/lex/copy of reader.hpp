#pragma once

#include <lex/token.hpp>
#include <chars/categories.hpp>

namespace lex {
  class Reader;
}

class lex::Reader {
public:
  Reader();
  Reader(dt::StrView input);

  void Skip(chars::Alphabet to_skip);
  void Skip(uint n);
  void SkipUntil(char);

  dt::StrView Read(chars::Alphabet to_read);
  dt::StrView ReadUntil(char);
  dt::StrView ReadGroup(char open_close);
  dt::StrView ReadGroup(char open, char close);
  dt::StrView ReadBalancedGroup(char open, char close);
  u64 ReadM9(chars::Alphabet);

  char PeekCurrent() const noexcept;
  char PeekNext() const noexcept;
  char PeekPrev() const noexcept;

  bool TryConsume(char);
  bool TryConsume(const char* cstr);

  bool CanRead() const noexcept;

protected:
  const char* pos;
  const char* pos_max;

  const char* PosAfter(chars::Alphabet);
  const char* PosAfter(chars::Alphabet, chars::Alphabet);
  const char* PosAfter(char);

  template<class F> dt::StrView Slurp(F scanning_fn) {
    const char* begin = pos;
    scanning_fn();
    return dt::StrView{begin, pos};
  }
};

// AbstractReader - ctors
//  SpacelessReader - read methods, skipping SPACES
