#pragma once

#define OR(A, B) \
  [&](){ \
    auto a_ = A; \
    return a_ ? a_ : B; \
  }()
