#include "dbg/sym.hpp"

#include <cstdio>

using namespace sym;

void dbg::dump(sym::Type ty) {
  switch (ty.Tag()) {
  case Type::VOID: puts("<VOID>"); break;
  case Type::ANY: puts("<ANY>"); break;
  case Type::INT: puts("<INT>"); break;
  case Type::REAL: puts("<REAL>"); break;
  case Type::NUM: puts("<NUM>"); break;
  case Type::STR: puts("<STR>"); break;

  default:
    puts("<UNKNOWN>");
  }
}
