#include <stdio.h>
#include "vec.h"

int main(void) {
  long score = 0;

  IntArr vals = arri_new(20);
  for (int i = 0; i < 20; ++i) vals.mem[i] = i * i;
  
  for (int i = 1; i < 50000; ++i) {
    CharVec vecc = vecc_new(i);
    IntVec veci = veci_new(i);

    for (int n = 0; n < 50; ++n) {
      vec_push(&vecc, (char)(n + 50));
      vec_push(&veci, n);
    }
    vec_push_arr(&veci, &vals);

    while (vecc.len) {
      score += vec_wild_pop(&vecc);
    }
    while (veci.len) {
      score += vec_wild_pop(&veci);
    }

    vec_free(&vecc);
    vec_free(&veci);
  }

  arr_free(&vals);
  printf("%ld\n", score);
  
  return 0;
}
