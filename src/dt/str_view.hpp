#pragma once

#include "typedefs.hpp"

namespace dt {
  class StrView;
}

class dt::StrView {
public:
  StrView() = default;
  StrView(const char* cstr);
  StrView(const char* bytes, u32 count);

  const char* Data() const noexcept;
  u32 Len() const noexcept;

  bool operator<(const StrView& other) const;
  bool operator==(const StrView& other) const;
  char operator[](std::size_t pos) const;

  bool IsEmpty() const noexcept;

  dt::StrView Truncate(uint n) const noexcept;

private:
  const char* data;
  u32 len;
};

static_assert(
  sizeof(dt::StrView) == 16 || sizeof(dt::StrView) == 8,
  "type size expectations failed"
);
