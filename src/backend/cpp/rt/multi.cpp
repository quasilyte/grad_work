#include "any.hpp"
#include <cstdio>
#include <vector>
#include <utility>

// benchmarks
const Int_ N = 10_i;
const Int_ M = 79999_i;

Int_ intint(Int_ a, Int_ b) {
  Int_ score = a;
  for (Int_ i = 0_i; i < N * a; i += 1) {
    score += a + b;
    if (score < N) {
      score += 10;
    } else {
      score -= a * 3;
    }
  }
  return score;
}

Int_ intreal(Int_ a, Real_ b) {
  Int_ score = a;
  for (Int_ i = 0_i; i < N * a; i += 1) {
    score += a + int_(b);
    if (score < N) {
      score += 10;
    } else {
      score -= a * 3;
    }
  }
  return score;
}

Int_ intany(Int_ a, Any_ b) {
  Int_ score = a;
  for (Int_ i = 0_i; i < N * a; i += 1) {
    score += a + int_(b);
    if (score < N) {
      score += 10;
    } else {
      score -= a * 3;
    }
  }
  return score;
}

Real_ realreal(Real_ a, Real_ b) {
  Real_ score = a;
  for (Real_ i = 0.0_r; i < N * a; i += 1.0) {
    score += a + b;
    if (score < N) {
      score += 10.0;
    } else {
      score -= a * 3.0;
    }
  }
  return score;
}

Real_ realint(Real_ a, Int_ b) {
  Real_ score = a;
  for (Real_ i = 0.0_r; i < N * a; i += 1.0) {
    score += a + real_(b);
    if (score < N) {
      score += 10.0;
    } else {
      score -= a * 3.0;
    }
  }
  return score;
}

Real_ realany(Real_ a, Any_ b) {
  Real_ score = a;
  for (Real_ i = 0.0_r; i < N * a; i += 1.0) {
    score += a + real_(b);
    if (score < N) {
      score += 10.0;
    } else {
      score -= a * 3.0;
    }
  }
  return score;
}

Any_ anyany(Any_ a, Any_ b) {
  Any_ score = a;
  for (Any_ i = any_(0_i); int_(i) < N * int_(a); i = any_(int_(i) + 1)) {
    score = any_(int_(score) + int_(a) + int_(b));
    if (int_(score) < N) {
      score = any_(int_(score) + 10);
    } else {
      score = any_(int_(score) - (int_(a) * 3));
    }
  }
  return score;
}

/*
Any_ test_any2(Any_ argc) {
  Any_ score = argc;
  for (Any_ i = any_(0_i); int_(i) < N * int_(argc); i = any_(int_(i) + 1)) {
    score = any_(int_(score) + (int_(i) % 6));
    if (int_(score) < N) {
      score = any_(int_(score) + 10);
    } else {
      score = any_(int_(score) - (int_(argc) * 3));
    }
  }
  return score;
}

Any_ test_any1(Any_ a, Any_ b) {
  Any_ score = argc;
  for (Any_ i = any_(0_i); int_(i) < M * int_(argc); i = any_(int_(i) + 1)) {
    score = any_(int_(score)
                 + int_(test_any2(a))
                 + int_(test_any2(b)));
  }
  return score;
}
*/

Any_ test_any1(Any_ a, Any_ b) {
  Any_ score = b;
  for (Any_ i = any_(0_i); int_(i) < M * int_(a); i = any_(int_(i) + 1)) {
    score = any_(int_(score) + int_(anyany(a, b)));
  }
  return score;
}

Any_ test_spec2(Any_ a, Any_ b) {
  switch (a.tag) {
  case Any_::INT: 
    switch (b.tag) {
    case Any_::INT: return any_(intint(int_(a), int_(b)));
    case Any_::REAL: return any_(intreal(int_(a), real_(b)));
    default: return any_(intany(int_(a), b));
    }
  case Any_::REAL:
    switch (b.tag) {
    case Any_::INT: return any_(realint(real_(a), int_(b)));
    case Any_::REAL: return any_(realreal(real_(a), real_(b)));
    default: return any_(realany(real_(a), b));
  }
  default: return anyany(a, b);
  }
}

Any_ test_spec1(Any_ a, Any_ b) {
  Any_ score = b;
  for (Any_ i = any_(0_i); int_(i) < M * int_(a); i = any_(int_(i) + 1)) {
    score = any_(int_(score) + int_(test_spec2(a, b)));
  }
  return score;
}

Int_ test_native(Int_ a, Int_ b) {
  Int_ score = b;
  for (Int_ i = 0_i; i < M * a; i += 1) {
    score += intint(a, b);
  }
  return score;
}

int main(int argc, char* argv[]) {
  Int_ score = 0_i;
  /*
  std::vector<Num*> xs = {
    new Int(2_i),
    new Int(3_i),
    new Real(4.0_r),
    new Int(1_i)
  };

  for (Num* x : xs) {
    score += x->calc();
    }*/

  /*
  std::vector<std::pair<Any_, Any_>> xs = {
    {any_(2_i), any_(1_i)},
    {any_(3_i), any_(1.0_r)},
    {any_(4.0_r), any_(2.0_r)},
    {any_(1_i), any_(0_i)},
  };
  
  for (auto x : xs) {
    score += int_(test_any1(x.first, x.second));
    // score += int_(test_spec1(x.first, x.second));
  }
  */

  std::vector<std::pair<Int_, Int_>> xs = {
    {2_i, 1_i},
    {3_i, 1_i},
    {4_i, 2_i},
    {1_i, 0_i},
  };
  
  for (auto x : xs) {
    score += test_native(x.first, x.second);
    // score += int_(test_any1(x.first, x.second));
    // score += int_(test_spec1(x.first, x.second));
  }

  printf("%ld\n", int_(score));
  return 0;
}
