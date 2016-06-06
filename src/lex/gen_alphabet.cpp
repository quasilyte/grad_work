#include <lex/gen_alphabet.hpp>

const int* lex::new_whitelist(const char* pattern) {
  int* whitelist = new int[255](); // All to 0

  for (const char* p = pattern; *p; ++p) {
    whitelist[static_cast<int>(*p)] = 1;
  }

  return whitelist;
}

const int* lex::new_blacklist(const char* pattern) {
  int* blacklist = new int[255];
  for (int i = 0; i < 255; ++i) blacklist[i] = 1;

  for (const char* p = pattern; *p; ++p) {
    blacklist[static_cast<int>(*p)] = 0;
  }

  return blacklist;
}
