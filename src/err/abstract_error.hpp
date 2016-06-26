#pragma once

#include <sym/type.hpp>

namespace err {
  struct AbstractError;
}

struct err::AbstractError {
  typedef const char*(*TypeMapper)(sym::Type);

  virtual void Blame(const char* error_location) const = 0;

  static void SetTypeMapper(TypeMapper);

protected:
  static TypeMapper name_by_type;
};
