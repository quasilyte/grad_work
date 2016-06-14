#include <xtern/pkg_parser.hpp>

#include <sym/type.hpp>
#include <lex/cursor.hpp>
#include <lex/gen_alphabet.hpp>
#include <lex/char_groups.hpp>
#include <dt/str_view.hpp>
#include <deps/c/stdio.hpp>
#include <dbg/dt.hpp>
#include <mn_hash.hpp>
#include <xtern/pkg_encode.hpp>

using namespace xtern;
using namespace lex;
using sym::Type;

const int* SPACES = new_whitelist(" \n\r\t\v");

void expect(bool expectation, const char* msg) {
  if (!expectation) {
    throw msg;
  }
}

sym::Type type_by_name(dt::StrView type_name) {
  using namespace mn_hash;

  switch (encode9(type_name.Data(), type_name.Len())) {
  case "Int"_m9: return Type::Int();
  case "Real"_m9: return Type::Real();
  case "Str"_m9: return Type::Str();
  case "Void"_m9: return Type::Void();

  default:
    throw "unknown type";
  }
}

Cursor cur;
io::FileWriter output;

sym::ParamList collect_params() {
  sym::ParamList params;

  while (!try_consume(skip(&cur, SPACES), ')')) {
    auto param_name = read(&cur, WORD);
    expect(try_consume(&cur, ':'), "expected `:`");
    auto param_type = type_by_name(read(&cur, WORD));

    params.push_back(sym::Param{param_name, param_type});
  }

  return params;
}

// func_b(one:Real two:Str):Void
sym::MonoFn eval_fn_decl() {
  auto name = read(skip(&cur, SPACES), WORD);
  expect(try_consume(skip(&cur, SPACES), '('), "expected `(`");
  auto params = collect_params();
  expect(try_consume(&cur, ':'), "expected `:`");
  auto ret_type = type_by_name(read(skip(&cur, SPACES), WORD));

  return sym::MonoFn{
    name,
    std::move(params),
    ret_type,
    0
  };
}

void parse_fn_decl() {
  auto fn = eval_fn_decl();
  encode_fn(output, fn);
}

/*
(f1 () Void)
(f2 () Int)
(f3 (a:Int) Int)

{File}
{Point x:Int y:Int}
*/

void parse_module() {
  encode_string(output, read(&cur, WORD));
  expect(try_consume(skip(&cur, SPACES), '{'), "expect `{`");

  while (!try_consume(skip(&cur, SPACES), '}')) {
    parse_fn_decl();
  }

  encode_byte(output, '#');
}

void parse_modules() {
  while (can_read(skip(&cur, SPACES))) {
    parse_module();
  }
}

void xtern::parse_pkg(const char *input, io::FileWriter fw) {
  cur = Cursor{input};
  output = fw;

  parse_modules();
}
