#include <test_lex/suite.hpp>

#include <chars/categories.hpp>
#include <test_utils.hpp>
#include <bench_utils.hpp>
#include <init_utils.hpp>

void init() {
  init_char_categories();
}

int main() {
  init();

  RUN(sanity);
  RUN(skip_and_peek);
  RUN(basic_read);
  RUN(advanced_read);
  RUN(consuming_functions);
  RUN(looping);
  RUN(comment_skip);

  FINISH();
}
