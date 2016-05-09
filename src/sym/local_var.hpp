#pragma once

namespace dt {
  class StrView;
}

namespace sym {
  class Type;
  struct LocalVar;
}

struct sym::LocalVar {
  const sym::Type* type;
  const dt::StrView* bound_name;
};

