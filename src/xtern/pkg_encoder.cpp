#include <xtern/pkg_encoder.hpp>

#include <deps/c/string.hpp>
#include <deps/c/stdlib.hpp>

using namespace xtern;

PkgEncoder::~PkgEncoder() {
  std::free(buf);
}

void PkgEncoder::EncodeByte(char byte) {
  Write(static_cast<char>(byte));
}

void PkgEncoder::EncodeType(sym::Type type) {
  auto tag = type.Tag();
  Write(reinterpret_cast<char*>(&tag), sizeof(sym::TypeId));
}

void PkgEncoder::EncodeString(const char *bytes, u32 count) {
  Write(static_cast<char>(count));
  Write(bytes, count);
}

void PkgEncoder::Write(char byte) {
  EnsureCapacity(1);
  buf[len] = byte;

  len += 1;
}

void PkgEncoder::Write(const char *bytes, u32 count) {
  EnsureCapacity(count);
  std::memcpy(buf + len, bytes, count);

  len += count;
}

void PkgEncoder::EnsureCapacity(int n) {
  if ((len + n) > cap) {
    cap *= 2;
    buf = static_cast<char*>(std::realloc(buf, cap));
  }
}
