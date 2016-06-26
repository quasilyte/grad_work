#pragma once

#include <err/abstract_error.hpp>

namespace err {
  struct NoExpectedChar;
  struct NoExpectedCstr;
  struct UnclosedLiteral;
  struct UnbalancedGroup;
}

struct err::NoExpectedChar: AbstractError {
  NoExpectedChar(char expected, char got);

  void Blame(const char* error_location) const override;

  char expected;
  char got;
};

/*
struct err::NoExpectedCstr {
  const char* expected;
};

struct err::UnclosedLiteral {
  char open_close;
};

struct err::UnbalancedGroup {
  char open;
  char close;
};
*/
