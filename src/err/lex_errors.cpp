#include <err/lex_errors.hpp>

#include <macro/blame.hpp>

using namespace err;

NoExpectedChar::NoExpectedChar(char expected, char got):
expected{expected}, got{got} {}

void NoExpectedChar::Blame(const char* error_location) const {
  BLAME(
    "expected {%c} char, found {%c}",
    error_location,
    expected,
    got
  );
}
