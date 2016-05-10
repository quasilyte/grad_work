#pragma once

namespace dt {
  class StrView;
}

namespace sym {
  class Type;
  struct LocalVar;
}

struct sym::LocalVar {
  sym::Type type;
  const dt::StrView* name;
};
