#include "sym/generator.hpp"

#include "io/utils.hpp"
#include <cstdlib>

using namespace sym;

Generator::Generator(): current_id{0}, count{32} {
  pool = static_cast<dt::StrView*>(std::malloc(sizeof(dt::StrView) * count));
}

u64 Generator::NextId() {
  char* buf = new char[10];
  buf[0] = 't';
  io::write_to_buf(buf + 1, current_id);

  pool[current_id] = dt::StrView{buf, 2};
  return current_id++;
}

const dt::StrView* Generator::Next() {
  return Get(NextId());
}

// const dt::StrView* Generator::Get(u64 id) {
const dt::StrView* Generator::Get(u64 id) {
  return &pool[id];
}

Generator::~Generator() {
  std::free(pool);
}
