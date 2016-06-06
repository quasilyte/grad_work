#pragma once

namespace go_cc {
  struct FnDecl;

  void declare_fn(const FnDecl&);
  void define_fn(const FnDecl&);
}
