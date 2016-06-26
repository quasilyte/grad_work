#pragma once

#include <typedefs.hpp>

namespace io {
  struct Buf;
}

struct io::Buf {
  char* data;
  u64 size;
};
