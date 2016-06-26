#pragma once

#include <err/abstract_error.hpp>
#include <dt/str_view.hpp>

namespace err {
  struct UndefinedSymbol;
}

struct err::UndefinedSymbol: AbstractError {
  UndefinedSymbol(dt::StrView name);

  void Blame(const char* error_location) const override;

  dt::StrView name;
};
