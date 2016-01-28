#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

#include "lexer/token.hpp"
#include "lexer/char_type.hpp"
#include "lexer/token_stream.hpp"

inline bool token_has_value(Token *tok) {
  return WORD == tok->tag || DECIMAL == tok->tag || REAL == tok->tag;
}

inline void test_checksum(const char *input, int expected_sum) {
  int sum = 0;
  TokenStream tokens(input, strlen(input));

  while (tokens.next_tag() != SOURCE_END) {
    switch (tokens.current()->tag) {
    case PLUS: sum += 1; break;
    case PLUS2: sum += 2; break;
    case MINUS: sum -= 1; break;
    case MINUS2: sum -= 2; break;
    case DECIMAL: sum += tokens.current()->len; break;
    case WORD: sum -= tokens.current()->len; break;
    case LPAREN: sum += 4; break;
    case RPAREN: sum += 8; break;
    case SEMICOLON: sum += 101; break;
    default: sum += 1;
    }
  }

  assert(sum == expected_sum);
}

inline void test_tags(const char *input, std::vector<TokenTag> expected_tags) {
  std::vector<TokenTag> tags;
  TokenStream tokens(input, strlen(input));

  while (tokens.next_tag() != SOURCE_END) {
    tags.push_back(tokens.current()->tag);
  }

  assert(tags == expected_tags);
}

inline void test_values(const char *input, std::vector<std::string> expected_values) {
  std::vector<std::string> values;
  TokenStream tokens(input, strlen(input));

  while (tokens.next_tag() != SOURCE_END) {
    if (token_has_value(tokens.current())) {
      values.push_back(std::string(tokens.current()->value, tokens.current()->len));
    }
  }

  assert(values == expected_values);
}

inline void run_test_checksums() {
  test_checksum(" four + 22   - (f) + (1) -- ++ ++ ", 25);
  test_checksum(" x -= 10; y += 20 ; ", 206);
}

inline void run_test_tags() {
  std::vector<TokenTag> input1 {PLUS, PLUS, MINUS, PLUS2};
  test_tags("+ + - ++ ", input1);

  std::vector<TokenTag> input2 {WORD, LPAREN, RPAREN, DECIMAL};
  test_tags("hello ( ) 1932 ", input2);

  std::vector<TokenTag> input3 {SEMICOLON, SEMICOLON, SEMICOLON, REAL, REAL};
  test_tags(";;; 98.5  1.1 ", input3);
}

inline void run_test_values() {
  std::vector<std::string> values1 {"word", "a", "5000", "1.90"};
  test_values("(word) + a - 5000;; 1.90 ", values1);

  std::vector<std::string> values2 {"long_name_with_underscores", "00"};
  test_values("  ++  long_name_with_underscores     00 // ", values2);
}

#define TEST(NAME) run_test_##NAME(); puts(#NAME " passed!");
#define FINISH(CODE) puts("\tall tests are passed"); return CODE;

int main(void) {
  TEST(checksums);
  TEST(tags);
  TEST(values);

  FINISH(0);
}
