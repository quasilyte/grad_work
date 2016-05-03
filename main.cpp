#include "lex/token_stream.hpp"
#include <cstring>
#include <cstdio>

using namespace lex;

int main() {
  auto input = "+ (10)";
  TokenStream ts(input, strlen(input));

  while (ts.next_tag() != SOURCE_END) {
    printf("%d\n", ts.current_tag());
  }

  return 0;
}
