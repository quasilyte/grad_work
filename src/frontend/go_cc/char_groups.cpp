#include <frontend/go_cc/char_groups.hpp>

#include <dev_assert.hpp>
#include <lex/gen_alphabet.hpp>

using namespace go_cc;

const int* go_cc::HOR_SPACES = nullptr;
const int* go_cc::SPACES = nullptr;
const int* go_cc::IDENT = nullptr;
const int* go_cc::NON_TERMINAL = nullptr;

void go_cc::init_char_groups() {
  dev_assert(nullptr == SPACES
             && nullptr == HOR_SPACES
             && nullptr == IDENT
             && nullptr == NON_TERMINAL);

  HOR_SPACES = lex::new_whitelist(" \t");
  SPACES = lex::new_whitelist(" \t\v\n\r;");
  IDENT = lex::new_whitelist(
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  );
  NON_TERMINAL = lex::new_blacklist(";\n\0");
}
