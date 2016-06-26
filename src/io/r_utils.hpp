#pragma once

#include <io/buf.hpp>

namespace io {
  Buf get_file_bytes(const char* file_path);
}
