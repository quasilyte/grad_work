#include "io/file_writer.hpp"

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
    close();
  }
}

void FileWriter::close() {
  std::fclose(file);
  file = nullptr;
}

void FileWriter::write(char ch) {
  std::fputc(ch, file);
}

void FileWriter::write(const char *cstr) {
  write(cstr, std::strlen(cstr));
}

void FileWriter::write(const char *bytes, u32 len) {
  std::fwrite(bytes, 1, len, file);
}
