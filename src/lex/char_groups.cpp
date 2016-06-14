#include <lex/char_groups.hpp>

#include <lex/gen_alphabet.hpp>

#include <dev_assert.hpp>

using namespace lex;

const int* lex::DIGITS = nullptr;
const int* lex::WORD = nullptr;

void lex::init_char_groups() {
  dev_assert(nullptr == DIGITS &&
             nullptr == WORD);

  DIGITS = new_whitelist("0123456789");

  WORD = new_whitelist(
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "_"
  );
}
