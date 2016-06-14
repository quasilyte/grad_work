#include <xtern/pkg_encode.hpp>

#include <dt/str_view.hpp>
#include <unit/fns.hpp>
#include <io/file_writer.hpp>
#include <dbg/dt.hpp>

using namespace xtern;
using dt::StrView;
using sym::Type;
using sym::ParamList;
using io::FileWriter;

void xtern::encode_byte(io::FileWriter& fw, char byte) {
  fw(byte);
}

void xtern::encode_type(io::FileWriter& fw, Type type) {
  auto tag = type.Tag();
  fw(reinterpret_cast<char*>(&tag), sizeof(sym::TypeId));
}

void xtern::encode_string(io::FileWriter& fw, const StrView& str) {
  encode_byte(fw, str.Len());
  fw(str);
}

StrView decode_string(const char** data) {
  u32 len = **data;
  *data += 1;
  const char* mem = *data;
  *data += len;

  return dt::StrView{mem, len};
}

Type decode_type(const char** data) {
  sym::TypeId tag = *(reinterpret_cast<const sym::TypeId*>(*data));
  *data += sizeof(sym::TypeId);

  return Type{tag};
}

char decode_byte(const char** data) {
  auto byte = **data;
  *data += 1;
  return byte;
}

void xtern::encode_fn(FileWriter& fw, const sym::MonoFn& fn) {
  encode_string(fw, fn.name);
  encode_type(fw, fn.ret_type);
  encode_byte(fw, fn.params.size());

  for (const sym::Param& param : fn.params) {
    encode_string(fw, param.name);
    encode_type(fw, param.type);
  }
}

void decode_fn(dt::StrView pkg_name, const char** data) {
  auto name = decode_string(data);
  auto ret_type = decode_type(data);
  auto arity = decode_byte(data);

  ParamList params;
  params.reserve(arity);

  for (int i = 0; i < arity; ++i) {
    auto param_name = decode_string(data);
    auto param_type = decode_type(data);
    params.push_back(sym::Param{param_name, param_type});
  }

  dbg::dump(name);
  dt::QualifiedId qid{pkg_name, name};


  // assign type_id
  // store in mono_fn_id_map
  // module_name.entry_name

  unit::ffn_register(qid, std::move(params), ret_type);
}

void decode_pkg(const char** data) {
  auto pkg_name = decode_string(data);
  dbg::dump(pkg_name);

  while ('#' != **data) {
    decode_fn(pkg_name, data);
  }

  *data += 1;
}

void xtern::decode_modules(const char* data) {
  while (*data) {
    decode_pkg(&data);
  }
}

