#include "dt/str_view.hpp"

#include <cstring>

using namespace dt;

StrView::StrView(const char* cstr):
data{cstr}, len{static_cast<u32>(std::strlen(cstr))} {}

StrView::StrView(const char* bytes, u32 count):
data{bytes}, len{count} {}

const char* StrView::Data() const noexcept {
  return data;
}

u32 StrView::Len() const noexcept {
  return len;
}

bool StrView::operator<(const StrView& other) const {
  if (len == other.len) {
    return std::strcmp(data, other.data) < 0;
  } else {
    return len < other.len;
  }
}

bool StrView::operator==(const StrView& other) const {
  return len == other.len && std::strncmp(data, other.data, other.len) == 0;
}
