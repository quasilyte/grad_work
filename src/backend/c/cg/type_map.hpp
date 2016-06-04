#pragma once

namespace sym {
  class Type;
  class Module;
}

namespace dt {
  class StrView;
}

namespace c_cg {
  dt::StrView& type_name(sym::Type);
  dt::StrView& intrinsic_name(sym::Type);
}
