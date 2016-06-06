#include <xtern/pkg_fn_encoder.hpp>

using namespace xtern;

using sym::ParamList;
using dt::StrView;
using sym::Type;

// [1][a][4][1]{[1][d][4]}
//  a     b  c   d     e c
//
// a - name length
// b - return type
// c - param count
// d - nth param name length
// e - nth param type id
void PkgFnEncoder::Encode(StrView name, Type ret_type, const ParamList& params) {
  EncodeString(name.Data(), name.Len());
  EncodeType(ret_type);
  EncodeByte(params.size());

  for (const sym::Param& param : params) {
    EncodeString(param.name.Data(), param.name.Len());
    EncodeType(param.type);
  }
}
