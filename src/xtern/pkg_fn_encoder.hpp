#pragma once

#include <xtern/pkg_encoder.hpp>
#include <dt/str_view.hpp>
#include <sym/typedefs.hpp>

namespace xtern {
  class PkgFnEncoder;
}

class xtern::PkgFnEncoder: public PkgEncoder {
public:
  void Encode(dt::StrView name, sym::Type ret_type, const sym::ParamList&);
};
