#include <io/utils.hpp>

#include <deps/c/stdio.hpp>

void io::write_to_buf(char *buf, u64 data) {
  // #FIXME: this is slow. Needs to be rewritten
  std::sprintf(buf, "%lu", data);
}
