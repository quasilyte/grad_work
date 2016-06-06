#pragma once

#include <xtern/pkg_encoder.hpp>
#include <dt/str_view.hpp>
#include <sym/typedefs.hpp>

namespace xtern {
  class PkgTypeEncoder;
}

class xtern::PkgTypeEncoder: public PkgEncoder {
public:
  void Encode(dt::StrView name, const sym::AttrList& attrs);
};
