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

  void DoSkip(uint n);
  void DoSkip(chars::Alphabet to_skip);
  void DoSkipUntil(char);
  void DoSkipLine();
  void DoSkipLiteral(char open_close);
  template<class COMMENT>
  void DoSkipGroup(char open, char close);

  dt::StrView Read(chars::Alphabet to_read);
  dt::StrView ReadUntil(char);
  dt::StrView ReadLine();
  dt::StrView ReadLiteral(char open_close);
  u64 ReadM9(chars::Alphabet);
  template<class COMMENT>
  dt::StrView ReadGroup(char open, char close);
  template<class TAGGER>
  Token ReadToken();

  char PeekCurrent() const noexcept;
  char PeekNext() const noexcept;
  char PeekPrev() const noexcept;

  bool TryConsume(char);
  bool TryConsume(const char* cstr);
  int TryConsume(chars::Alphabet to_consume);

  void MustConsume(char);
  void MustConsume(const char* cstr);

  bool CanRead() const noexcept;
  const char* Pos() const noexcept;

protected:
  const char* pos;
  const char* pos_max;
};

