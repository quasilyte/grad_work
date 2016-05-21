#include "io/file_writer.hpp"

#include "dt/str_view.hpp"
#include "dev_assert.hpp"

using namespace io;

FileWriter::FileWriter() {}

FileWriter::FileWriter(FILE* file): file{file} {}

void FileWriter::SetFile(FILE* file) {
  this->file = file;
}

void FileWriter::Close() {
  dev_assert(file != nullptr);

  std::fclose(file);
}

FileWriter FileWriter::operator()(char c) {
  std::fputc(c, file);
  return *this;
}

FileWriter FileWriter::operator()(const char* bytes, u32 amount) {
  std::fwrite(bytes, 1, amount, file);
  return *this;
}

FileWriter FileWriter::operator()(const dt::StrView& s) {
  std::fwrite(s.Data(), 1, s.Len(), file);
  return *this;
}
