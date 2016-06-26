#pragma once

namespace err {
  struct SyntaxError;
}

struct err::SyntaxError {
  const char* unexpected;
  const char* expected;
};
