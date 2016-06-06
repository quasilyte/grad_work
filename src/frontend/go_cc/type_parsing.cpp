#include <frontend/go_cc/type_parsing.hpp>

#include <unit/source.hpp>
#include <unit/structs.hpp>
#include <frontend/go_cc/decl.hpp>
#include <frontend/go_cc/char_groups.hpp>
#include <frontend/go_cc/cursor_ext.hpp>
#include <frontend/go_cc/types.hpp>
#include <errors.hpp>
#include <lex/cursor.hpp>
#include <deps/c/stdio.hpp>

using namespace go_cc;
using namespace lex;

void go_cc::declare_struct(const StructDecl& st_decl) {
  try {
    unit::declare_struct(st_decl.name);
  } catch (err::Redefinition e) {
    BLAME(
      "redefinition of {%.*s} {%s}",
      st_decl.name,
      BUF_FMT(e.name),
      e.type
    );
  }
}

void go_cc::define_struct(const StructDecl& st_decl) {
  auto st = unit::get_struct(st_decl.name);

  // If there is no struct inside `unit`, then it most likely
  // an error occured during `declare_struct`
  if (st) {
    try {
      sym::Struct::AttrList attrs;
      Cursor cur{st_decl.body};

      while (can_read(skip(&cur, SPACES))) {
        auto name = next_ident(&cur);
        auto type = type_by_name(next_ident(&cur));

        attrs.push_back(sym::Param{name, type});
      }

      st->Define(std::move(attrs));
    } catch (err::UndefinedType e) {
      BLAME(
        "unknown type {%.*s}",
        e.name,
        BUF_FMT(e.name)
      );
    }
  }
}
