#include <unit/fns.hpp>

#include <sym/fn.hpp>
#include <sym/type.hpp>
#include <dt/dict.hpp>
#include <deps/c/math.hpp>
#include <deps/cxx/vector.hpp>

using namespace unit;
using namespace sym;
using namespace dt;

std::vector<UnnamedFn*> unnamed_fns;

Dict<MultiFn*> multi_fn_name_map;
std::vector<MultiFn*> multi_fn_id_map;
std::vector<NamedFn*> named_fns;

Dict<MonoFn*> mono_fn_name_map;
std::vector<MonoFn*> mono_fn_id_map;

Type unit::new_unnamed_fn(ParamList&& params, ast::NodeList&& exprs, Type ret_ty) {
  auto type = Type::UnnamedFn(unnamed_fns.size());

  unnamed_fns.push_back(new UnnamedFn{
    type,
    std::move(params),
    std::move(exprs), ret_ty
  });

  return type;
}

Fn* unit::get_fn(Type ty) {
  switch ((ty).Tag()) {
  case Type::MONO_FN: return get_named_fn(ty);
  case Type::UNNAMED_FN: return get_unnamed_fn(ty);
  case Type::NAMED_FN: return get_mono_fn(ty);

  default: throw "get_fn: not a function";
  }
}

UnnamedFn* unit::get_unnamed_fn(Type ty) {
  return unnamed_fns[ty.Id()];
}

UnnamedFn* unit::get_unnamed_fn(uint id) {
  return unnamed_fns[id];
}

uint unit::unnamed_fn_count() {
  return unnamed_fns.size();
}

NamedFn* unit::declare_named_fn
(StrView name, ParamList&& params, const MultiFn::Key& key) {
  NamedFn* named_fn;
  auto multi_fn = multi_fn_name_map.Find(name);

  if (multi_fn) { // Has at least 1 definition
    if (multi_fn->arity != params.size()) {
      throw "declare_named_fn: arity mismatch";
    }

    auto found_dup = multi_fn->funcs.find(key) != multi_fn->funcs.end();

    if (found_dup) { // Has definition with same signature
      throw "declare_named_fn: func already defined";
    } else {
      named_fn = new NamedFn{
        multi_fn,
        std::move(params),
        Type::Unknown(),
        static_cast<u32>(multi_fn->funcs.size() + 1)
      };
      multi_fn->funcs[key] = named_fn;
    }
  } else { // First declaration, no overloadings yet
    multi_fn = new sym::MultiFn{
      Type::DynDispatcher(multi_fn_name_map.Size()),
      name,
      static_cast<uint>(params.size())
    };
    named_fn = new NamedFn{multi_fn, std::move(params), Type::Unknown(), 1};
    multi_fn->funcs[key] = named_fn;

    multi_fn_name_map.Put(name, multi_fn);
    multi_fn_id_map.push_back(multi_fn);
  }

  named_fns.push_back(named_fn);
  return named_fn;
}

NamedFn* unit::get_named_fn(Type ty) {
  return named_fns[ty.Id()];
}

NamedFn* unit::get_named_fn(uint idx) {
  return named_fns[idx];
}

uint unit::named_fn_count() {
  return named_fns.size();
}

MultiFn* unit::get_multi_fn(StrView name) {
  return multi_fn_name_map.Find(name);
}

MultiFn* unit::get_multi_fn(Type ty) {
  return multi_fn_id_map[ty.Id()];
}

MonoFn* unit::declare_mono_fn(StrView name, ParamList&& params, Type ret_type) {
  if (mono_fn_name_map.Find(name)) {
    throw "declare_mono_fn: already defined";
  } else {
    auto mono_fn = new MonoFn{
      name,
      std::move(params),
      ret_type,
      static_cast<u32>(mono_fn_name_map.Size())
    };

    mono_fn_name_map.Put(name, mono_fn);
    mono_fn_id_map.push_back(mono_fn);

    return mono_fn;
  }
}

MonoFn* unit::get_mono_fn(StrView name) {
  return mono_fn_name_map.Find(name);
}

MonoFn* unit::get_mono_fn(Type type) {
  return mono_fn_id_map[type.Id()];
}

MonoFn* unit::get_mono_fn(uint idx) {
  return mono_fn_id_map[idx];
}

uint unit::mono_fn_count() {
  return mono_fn_name_map.Size();
}
