#include "di/output.hpp"

#include "dev_assert.hpp"

FILE* m_file;
FILE* r_file;

void di::set_files(FILE *module, FILE *runtime) {
  dev_assert(nullptr == m_file && nullptr == r_file);
  dev_assert(module != runtime);

  if (module && runtime) {
    m_file = module;
    r_file = runtime;
  } else {
    throw "module or runtime file is null";
  }
}

void di::close_files() {
  dev_assert(nullptr != m_file && nullptr != r_file);

  fclose(m_file);
  fclose(r_file);
}

void di::module_write(const dt::StrView& s) {
  std::fwrite(s.Data(), 1, s.Len(), m_file);
}

void di::module_write(const char* bytes, u32 amount) {
  std::fwrite(bytes, 1, amount, m_file);
}

void di::module_write(char c) {
  std::fputc(c, m_file);
}

void di::runtime_write(const dt::StrView& s) {
  std::fwrite(s.Data(), 1, s.Len(), r_file);
}

void di::runtime_write(const char* bytes, u32 amount) {
  std::fwrite(bytes, 1, amount, r_file);
}

void di::runtime_write(char c) {
  std::fputc(c, r_file);
}
