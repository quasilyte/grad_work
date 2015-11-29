#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lex.h"
#include "arr.h"
#include "vec.h"

/*
static Buf get_input(void) {
  char* bss_cstr = "(+ 10 20)";
  size len = strlen(bss_cstr);
  char* heap_cstr = malloc(len + 1);

  strcpy(heap_cstr, bss_cstr);

  return (Buf) { .cap = len, .mem = heap_cstr };
}
*/

int main(void) {
  long score = 0;

  for (unsigned i = 1; i < 100000; ++i) {
    // char* mem = malloc(i);
    Vec vec = vec_new(i);

    for (int c = 60; c < 100; ++c) {
      // vec_push(&vec, c);
      score += c;
    }

    /*
    while (vec.current != vec.arr.mem) {
      score += vec_pop(&vec);
    }
    */
    
    // free(mem);
    vec_free(&vec);
  }
  
  printf("%ld\n", score);
  
  return 0;
}
