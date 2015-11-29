#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>

#define MODE 2

int main(void) {
  size_t score = 0;
  
#if MODE == 1
  setlocale(LC_ALL, "C.UTF-8");
  // len = 21
  wchar_t* str_utf8 = L"привет hello ちは! abcd";
  for (int i = 0; i < 1000000; ++i) {
    for (wchar_t* p = str_utf8; *p; ++p) {
      score += *p;
      score -= wcslen(str_utf8);
    }
  }
  wprintf(L"%ld\n", score); 
#else
  setlocale(LC_ALL, "C");
  // len = 21
  char* str_ascii = "anfi3jfkdncjgkfjdncjf";
  for (int i = 0; i < 1000000; ++i) {
    for (char* p = str_ascii; *p; ++p) {
      score += *p;
      score -= strlen(str_ascii);
    }
  }
  printf("%ld\n", score); 
#endif
  
  return 0;
}
