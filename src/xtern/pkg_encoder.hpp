#pragma once

#include <sym/type.hpp>

namespace xtern {
  class PkgEncoder;
}

class xtern::PkgEncoder {
protected:
  ~PkgEncoder();

  void EncodeByte(char byte);
  void EncodeType(sym::Type);
  void EncodeString(const char* bytes, u32 count);

  void Save(const char* dest_path);

private:
  usize len;
  usize cap;
  char* buf;

  void Write(const char* bytes, u32 count);
  void Write(char byte);

  void EnsureCapacity(int n);
};
