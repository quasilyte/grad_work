#include "frontend/go_cc/classifier.hpp"

#include "mn_hash.hpp"
#include "dbg/dt.hpp"
#include "unit/globals.hpp"
#include "unit/structs.hpp"
#include "sym/type.hpp"
#include "ast/literals.hpp"
#include "ast/defs.hpp"
#include <deps/c/string.hpp>
#include <deps/c/stdio.hpp>
#include "frontend/go_cc/char_groups.hpp"
#include "frontend/go_cc/types.hpp"
#include "frontend/go_cc/cursor_ext.hpp"

using namespace go_cc;
using namespace lex;
using sym::Type;

TopLevel Classifier::Run(const char* input_cstr) {
  Classifier self{input_cstr};
  return self.Classify();
}

Classifier::Classifier(const char* input_cstr): cur{lex::Cursor{input_cstr}} {}

TopLevel Classifier::Classify() {
  using mn_hash::operator "" _m9;

  while (can_read(skip(&cur, SPACES))) {
    auto keyword = read_m9(&cur, IDENT);

    switch (keyword) {
    case "var"_m9: ClassifyVar(); break;
    case "func"_m9: ClassifyFn(); break;
    case "type"_m9: ClassifyType(); break;

    default:

      throw "invalid top level declaration";
    }
  }

  return result;
}

void Classifier::ClassifyFn() {
  auto name = next_ident(&cur);
  auto params = read_group(skip(&cur, SPACES), '(', ')').Truncate(1);
  auto ret_type_name = next_ident(&cur);
  auto body = read_group(skip(&cur, SPACES), '{', '}').Truncate(1);

  auto ret_type = ret_type_name.IsEmpty()
      ? sym::Type::Void()
      : type_by_name(ret_type_name);

  result.fns.push_back(FnDecl{name, params, body, ret_type});
}

void Classifier::ClassifyVar() {
  auto name = next_ident(&cur);

  if (try_consume(skip(&cur, SPACES), '=')) {
    result.globals.push_back(Decl{name, next_expr(&cur)});
  } else {
    auto type = type_by_name(next_ident(&cur));

    if (try_consume(skip(&cur, SPACES), '=')) {
      result.typed_globals.push_back(
        TypedDecl{name, type, next_expr(&cur)}
      );
    } else {
      throw "expected `=` token";
    }
  }
}

void Classifier::ClassifyType() {
  using mn_hash::operator "" _m9;

  auto name = next_ident(&cur);
  auto type = next_ident(&cur);
  auto body = read_group(skip(&cur, SPACES), '{', '}').Truncate(1);

  if (type.Len() < 10) {
    switch (mn_hash::encode9(type.Data(), type.Len())) {
    case "struct"_m9:
      result.structs.push_back(StructDecl{name, body});
      break;

    case "interface"_m9: throw "no interfaces yet";
    default: throw "no type aliases yet";
    }
  } else {
    throw "no type aliases yet";
  }
}
