#include "dbg/sym.hpp"

#include <cstdio>

using namespace sym;

void dbg::dump(sym::Type ty) {
  switch (ty.Tag()) {
  case Type::VOID_ID: puts("<VOID>"); break;
  case Type::ANY_ID: puts("<ANY>"); break;
  case Type::INT_ID: puts("<INT>"); break;
  case Type::REAL_ID: puts("<REAL>"); break;
  case Type::NUM_ID: puts("<NUM>"); break;
  case Type::STR_ID: puts("<STR>"); break;
  case Type::UNKNOWN_ID: puts("<UNKNOWN>"); break;

  default:
    puts("<?!>");
  }
}
