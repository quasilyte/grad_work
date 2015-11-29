#include <stdio.h>
#include "char_arr.h"
#include "arr.h"
#include "char_vec.h"
#include "vec.h"

int main(void) {
  CharVec vecc = vecc_new(10);
  vec_push(&vecc, 'a');
  printf("%c\n", vecc_pop(&vecc));
  vec_free(&vecc);
  return 0;
}
