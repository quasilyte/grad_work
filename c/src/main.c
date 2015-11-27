#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lex.h"
#include "buf.h"

static Buf get_input(void) {
  char* bss_cstr = "(+ 10 20)";
  size len = strlen(bss_cstr);
  char* heap_cstr = malloc(len + 1);

  strcpy(heap_cstr, bss_cstr);

  return (Buf) { .cap = len, .mem = heap_cstr };
}

int main(void) {
  Buf input = get_input();
  Lex lex = lex_make(input);
  
  buf_free(&input);
  return 0;
}
