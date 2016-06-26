#pragma once

namespace err {
  struct FileNotFound;
}

struct err::FileNotFound {
  const char* path;
};
