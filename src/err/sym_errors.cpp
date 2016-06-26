#include <err/sym_errors.hpp>

#include <macro/blame.hpp>

using namespace err;

UndefinedSymbol::UndefinedSymbol(dt::StrView name): name{name} {}

void UndefinedSymbol::Blame(const char* error_location) const {
  BLAME("symbol {%.*s} is undefined", error_location, BUF_FMT(name));
}
