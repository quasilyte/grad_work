#include <frontend/go_cc/phase1/classifier.hpp>

#include <mn_hash.hpp>
#include <dbg/dt.hpp>
#include <unit/globals.hpp>
#include <unit/structs.hpp>
#include <sym/type.hpp>
#include <ast/literals.hpp>
#include <ast/defs.hpp>
#include <deps/c/string.hpp>
#include <deps/c/stdio.hpp>
#include <frontend/go_cc/common/types.hpp>
#include <frontend/go_cc/common/reader.hpp>
#include <chars/categories.hpp>
#include <lex/c/comment.hpp>

using namespace go_cc;
using namespace chars;
using sym::Type;

TopLevel Classifier::Run(const char* input_cstr) {
  Classifier self{input_cstr};
  return self.Classify();
}

Classifier::Classifier(const char* input_cstr):
reader{Reader{input_cstr}} {}

TopLevel Classifier::Classify() {
  using mn_hash::operator "" _m9;

  while (reader.Skip()->CanRead()) {
    switch (reader.ReadM9(C_IDENT)) {
    case "var"_m9: ClassifyVar(); break;
    case "func"_m9: ClassifyFn(); break;
    case "type"_m9: ClassifyType(); break;

    default:
      throw "expected var|func|type";
    }
  }

  return result;
}

void Classifier::ClassifyFn() {
  auto name = reader.Skip()->Read(C_IDENT);
  auto params = reader.Skip()->ReadGroup('(', ')');

  auto ret_type_name = reader.Skip()->Read(C_IDENT);

  auto body = reader.Skip()->ReadGroup('{', '}');

  auto ret_type = ret_type_name.IsEmpty()
      ? sym::Type::Void()
      : type_by_name(ret_type_name);

  result.fns.push_back(FnDecl{name, params, body, ret_type});
}

void Classifier::ClassifyVar() {
  auto name = reader.Skip()->Read(C_IDENT);

  if (reader.Skip()->TryConsume('=')) {
    auto expr = reader.Skip()->ReadExpr();
    result.globals.push_back(VarDecl{name, expr, Type::Unknown()});
  } else {
    auto type = type_by_name(reader.Read(C_IDENT));
    reader.Skip()->MustConsume('=');
    auto expr = reader.Skip()->ReadExpr();
    result.globals.push_back(VarDecl{name, expr, type});
  }
}

void Classifier::ClassifyType() {
  using mn_hash::operator "" _m9;

  auto name = reader.Skip()->Read(C_IDENT);
  auto type = reader.Skip()->Read(C_IDENT);
  auto body = reader.Skip()->ReadGroup('{', '}');

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
