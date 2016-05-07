#pragma once

#include "sym/type.hpp"
#include <vector>

namespace sym {
  class Signature;
}

// Вызов функции:
// - проверяет арность
// - выдаёт ошибки для строгих типов
// -
class sym::Signature {
public:
  int get_min_arity() const noexcept;
  int get_max_arity() const noexcept;

private:
  Type return_type;
  int min_arity;
  int max_arity;
  std::vector<Type> params;
};
