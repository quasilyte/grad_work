#pragma once

namespace sym {
  class Type;
  struct GlobalVar;
}

struct sym::GlobalVar {
  const sym::Type* type;
};
