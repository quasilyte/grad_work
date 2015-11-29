#include <stdio.h>
#include <string.h>
#include "vec.h"
#include "str.h"

int main(void) {
  long score = 0;
  
  for (int i = 0; i < 500000; ++i) {
    Str s = str_from_cstr("hello, world!");
    str_push_char(&s, 'a');
    str_push_cstr(&s, "xxx");
    str_set_char(&s, '?', 0);
    if (str_char_at(&s, 1) == '?') {
      score += 1;
    }
    score += str_len(&s);
    score += strlen(str_chars(&s));
    str_free(&s);
  }
  
  printf("%ld\n", score);
  
  return 0;
}
