#include <chars/alphabet.hpp>

using namespace chars;

const int ASCII_MAX = 127;

Alphabet Alphabet::FromWhitelist(const char* pattern) {
  int* whitelist = new int[ASCII_MAX](); // All to 0

  for (const char* p = pattern; *p; ++p) {
    whitelist[static_cast<int>(*p)] = 1;
  }

  return Alphabet{whitelist};
}

Alphabet Alphabet::FromBlacklist(const char *pattern) {
  int* whitelist = new int[ASCII_MAX];
  for (int i = 0; i < ASCII_MAX; ++i) whitelist[i] = 1;

  for (const char* p = pattern; *p; ++p) {
    whitelist[static_cast<int>(*p)] = 0;
  }

  return Alphabet{whitelist};
}

bool Alphabet::Contains(int ch) {
  return whitelist[ch];
}

Alphabet::Alphabet(const int* whitelist): whitelist{whitelist} {}
