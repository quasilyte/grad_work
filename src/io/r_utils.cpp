#include <io/r_utils.hpp>

#include <err/io_errors.hpp>
#include <err/fatal.hpp>
#include <deps/c/stdio.hpp>
#include <deps/c/stdlib.hpp>

using namespace io;

u64 get_file_size(FILE* file) {
  // #NOTE: should try stat instead of fseek
  std::fseek(file, 0, SEEK_END);
  u64 size = ftell(file);
  std::rewind(file);

  return size;
}

Buf io::get_file_bytes(const char *file_path) {
  FILE* file = std::fopen(file_path, "r");
  if (!file) { throw err::FileNotFound{file_path}; }

  u64 size = get_file_size(file);
  char* data = static_cast<char*>(std::malloc(size + 1));
  if (!data) {
    throw err::Fatal{"memory allocation failed during input file reading"};
  }

  std::fread(data, size, 1, file);
  data[size] = '\0';

  std::fclose(file);
  return Buf{data, size};
}
