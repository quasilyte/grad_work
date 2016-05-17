#include "any.h"
#include "array.h"

const Int_ N = 6999;
const Int_ M = 999;

long test_arr(int argc) {
  Int_ score = 0;
  struct ArrayHandle_Int_ arr = new_Array_Int_(N);
  for (Int_ i = 0; i < N * argc; ++i) {
    for (Int_ j = 0; j < M * argc * 3; ++j) {
      set_Array_Int_(arr, j, i + j);
    }
    for (Int_ j = 0; j < N; ++j) {
      if (argc) {
        score += nth_Array_Int_(arr, j);
      }
    }
  }
  return score;
}

int main(int argc, char* argv[]) {
  printf("%ld\n", test_arr(argc));
  return 0;
}
