#include <cstdio>

long mul(long a, long b) {
  return a * b;
}
double mul(double a, double b) {
  return a * b;
}

template<class A> A sqr(A x) {
  return mul(x, x);
}

int main(void) {
  printf("%f\n", sqr(3.3));
  printf("%ld\n", sqr(4L));
  
  return 0;
}
