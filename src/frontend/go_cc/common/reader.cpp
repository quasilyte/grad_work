#include <frontend/go_cc/common/reader.hpp>

#include <lex/c/comment.hpp>
#include <unit/structs.hpp>
#include <mn_hash.hpp>

using namespace go_cc;
using namespace chars;
using sym::Type;

dt::StrView Reader::ReadGroup(char open, char close) {
  return lex::Reader::ReadGroup<c_lex::Comment>(open, close);
}

dt::StrView Reader::ReadExpr() {
  if ('(' == PeekCurrent()) {
    return ReadGroup('(', ')');
  } else {
    return ReadLine();
  }
}

Type Reader::ReadType() {
  /*
  using namespace mn_hash;

  auto type_name = Read(C_IDENT);

  switch (encode9(type_name.Data(), type_name.Len())) {
  case "int"_m9: return Type::Int();
  case "int64"_m9: return Type::Int();
  case "float64"_m9: return Type::Real();
  case "string"_m9: return Type::Str();

    /*
  case "func"_m9:
    auto params = ReadGroup('(', ')');
    auto ret_type = ReadType();


  default:
    auto st = unit::get_struct(type_name);

    if (st) {
      return st->type;
    } else {
      throw err::UndefinedType{type_name};
    }
  }*/
}

Reader* Reader::Skip(chars::Alphabet to_skip) {
  DoSkip(to_skip);
  return this;
}

Reader* Reader::Skip(uint n) {
  DoSkip(n);
  return this;
}
