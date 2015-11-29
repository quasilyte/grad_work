#include <stdio.h>
#include "vec.h"

int main(void) {
  long score = 0;

  for (int i = 1; i < 50000; ++i) {
    CharVec vecc = vecc_new(i);
    IntVec veci = veci_new(i);

    for (int n = 0; n < 50; ++n) {
      vec_push(&vecc, (char)(n + 50));
      vec_push(&veci, n);
    }

    while (vecc.len && veci.len) {
      score += vec_wild_pop(&vecc);
      score += vec_wild_pop(&veci);
    }

    vec_free(&vecc);
    vec_free(&veci);
  }

  printf("%ld\n", score);
  
  return 0;
}
