#include "sym/generator.hpp"

#include "io/utils.hpp"
#include "fmt/uint.hpp"
#include <cstdlib>

using namespace sym;

Generator::Generator(char prefix):
prefix{prefix}, current_id{0}, count{32} {
  pool = static_cast<dt::StrView*>(std::malloc(sizeof(dt::StrView) * count));
}

Generator::Id Generator::NextId() {
  auto len = fmt::width(current_id) + 1;

  char* buf = new char[len];
  buf[0] = prefix;
  io::write_to_buf(buf + 1, current_id);

  pool[current_id] = dt::StrView{buf, len};

  return current_id++;
}

const dt::StrView* Generator::Next() {
  return Get(NextId());
}

const dt::StrView* Generator::Get(Id id) {
  return &pool[id];
}

void Generator::Drop(int n) {
  current_id -= n;
}

Generator::~Generator() {
  // std::free(pool);
}
