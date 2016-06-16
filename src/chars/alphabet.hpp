#pragma once

namespace chars {
  class Alphabet;
}

class chars::Alphabet {
public:
  static Alphabet FromWhitelist(const char*);
  static Alphabet FromBlacklist(const char*);

  Alphabet() = default;

  bool Contains(int ch);

private:
  const int* whitelist;  

  Alphabet(const int* alphabet);
};
