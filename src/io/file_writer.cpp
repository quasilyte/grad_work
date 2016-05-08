#include "io/file_writer.hpp"

#include "sym/sym.hpp"
#include <cstring>

using namespace io;

FileWriter::FileWriter(): file{stdout} {}

FileWriter::FileWriter(const char *file_path):
file{std::fopen(file_path, "w")} {
  if (!file) {
    throw FileNotFound{};
  }
}

FileWriter::~FileWriter() {
  if (file) {
    Close();
  }
}

void FileWriter::Write(char ch) const {
  std::fputc(ch, file);
}

void FileWriter::Write(const char *cstr) const {
  Write(cstr, std::strlen(cstr));
}

void FileWriter::Write(const char *bytes, u32 len) const {
  std::fwrite(bytes, 1, len, file);
}

void FileWriter::Write(const dt::StrView& str_view) const {
  Write(str_view.Data(), str_view.Len());
}

void FileWriter::WriteMangled(const dt::StrView& str_view) const {
  Write('v');

  for (uint i = 0; i < str_view.Len(); ++i) {
    Write(sym::mangle(*(str_view.Data() + i)));
  }
}

void FileWriter::Close() {
  std::fclose(file);
  file = nullptr;
}
