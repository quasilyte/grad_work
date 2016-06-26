#include <sym/generator.hpp>

#include <io/w_utils.hpp>
#include <fmt/uint.hpp>
#include <deps/c/stdlib.hpp>
#include <deps/c/stdio.hpp>
#include <dev_assert.hpp>

using namespace sym;

Generator::Generator(char prefix, int cap): prefix{prefix} {
  pool.reserve(cap);
}

Generator::Id Generator::NextId() {
  if (pool[current_id].Data() == nullptr) {
    Generate(current_id);
  }

  return current_id++;
}

Generator::Id Generator::CurrentId() const noexcept {
  return current_id;
}

const dt::StrView& Generator::GetNext() {
  return Get(NextId());
}

const dt::StrView& Generator::Get(Id id) {
  dev_assert(pool[id].Data() != nullptr);

  return pool[id];
}

void Generator::GenerateAll() {
  for (Id i = current_id; i < pool.capacity(); ++i) {
    Generate(i);
  }
}

void Generator::Generate(Id id) {
  dev_assert(pool[id].Data() == nullptr);

  auto len = fmt::width(id) + 1; // extra byte for prefix

  char* buf = new char[len];
  buf[0] = prefix;
  io::write_to_buf(buf + 1, id);

  pool.push_back(dt::StrView{buf, len});
}

Generator::~Generator() {
  puts("cleanup");
}
