#include <xtern/pkg_type_encoder.hpp>

using namespace xtern;

#include <sym/attr.hpp>

using sym::AttrList;
using dt::StrView;
using sym::Type;

// [1][a][1]{[1][c][4]}
//  a     b   c     d b
//
// a - name length
// b - attr count
// c - nth attr name length
// d - nth attr type id
void PkgTypeEncoder::Encode(StrView name, const AttrList& attrs) {
  EncodeString(name.Data(), name.Len());
  EncodeByte(attrs.size());

  for (const sym::Attr& attr : attrs) {
    EncodeString(attr.name.Data(), attr.name.Len());
    EncodeType(attr.type);
  }
}
