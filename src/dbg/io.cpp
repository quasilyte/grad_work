#include "dbg/io.hpp"

#include <fstream>
#include <cassert>

std::string slurp(const char *name) {
  std::ifstream input{name};
  assert(nullptr != input);
  return std::string(
    std::istreambuf_iterator<char>{input},
    std::istreambuf_iterator<char>{}
  );
}
