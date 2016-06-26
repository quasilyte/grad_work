#pragma once

namespace err {
  struct Fatal;
}

struct err::Fatal {
  const char* message;
};
