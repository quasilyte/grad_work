#include <dt/str_view.hpp>

#include <deps/c/string.hpp>

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

char StrView::operator[](std::size_t pos) const {
  return data[pos];
}

bool StrView::IsEmpty() const noexcept {
  return Len() == 0;
}

dt::StrView StrView::Truncate(uint n) const noexcept {
  return dt::StrView{data + n, len - n * 2};
}
