#include "array.hpp"
#include <vector>

const Int_ N = 6999;
const Int_ M = 999;

long test_arr(int argc) {
  Int_ score = 0;
  auto arr = Arrays_::New(N);
  for (Int_ i = 0; i < N * argc; ++i) {
    for (Int_ j = 0; j < M * argc * 3; ++j) {
      set_(arr, j, i + j);
    }
    for (Int_ j = 0; j < N; ++j) {
      if (argc) {
        score += nth_(arr, j);
      }
    }
  }
  return score;
}

long test_vec(int argc) {
  Int_ score = 0;
  auto arr = std::vector<Int_>{N};
  for (Int_ i = 0; i < N * argc; ++i) {
    for (Int_ j = 0; j < M * argc * 3; ++j) {
      arr[j] = i + j;
    }
    for (Int_ j = 0; j < N; ++j) {
      if (argc) {
        score += arr[j];
      }
    }
  }
  return score;
}

int main(int argc, char* argv[]) {
  // printf("%ld\n", test_arr(argc));
  printf("%ld\n", test_vec(argc));
  
  return 0;
}
