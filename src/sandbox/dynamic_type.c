#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

typedef int64_t i64;
typedef double f64;

#define DECIMAL 0
#define REAL 1
#define ARRAY 2
#define CASE(cond, code) case cond: code; break;

typedef struct Box Box;
struct Box;

typedef struct Array Array;
struct Array {
  size_t cap;
  size_t len;
  Box* boxes;
};

struct Box {
  int type;
  union {
    i64 decimal;
    f64 real;
    Array array;
  } value;
};

Array array_new_empty(void) {
  return (Array) {
    .cap = 0,
    .len = 0,
    .boxes = NULL,
  };
}

void array_free(Array* arr) {
  if (0 != arr->cap) {
    free(arr->boxes);
  }
}

void array_push(Array* arr, Box* box) {
  arr->boxes[arr->len++] = *box;
}

void array_set(Array* arr, size_t index, Box* box) {
  arr->boxes[index] = *box;
}

Box* array_get(Array* arr, size_t index) {
  return &arr->boxes[index];
}

Array array_new(size_t initial_cap) {
  Array arr = {
    .cap = initial_cap,
    .len = 0
  };
  arr.boxes = malloc(initial_cap * sizeof(Box));
  return arr;
}

i64 box_to_decimal(Box* box) {
  switch (box->type) {
    CASE(DECIMAL, return box->value.decimal);
    CASE(REAL, return (i64) box->value.real);
  }
}

f64 box_to_real(Box* box) {
  switch (box->type) {
    CASE(DECIMAL, return (f64) box->value.decimal);
    CASE(REAL, return box->value.real);
  }
}

void box_add(Box* a, Box* b) {
  switch (a->type) {
    CASE(DECIMAL, a->value.decimal += box_to_decimal(b));
    CASE(REAL, a->value.real += box_to_real(b));
  }
}

void box_sub(Box* a, Box* b) {
  switch (a->type) {
    CASE(DECIMAL, a->value.decimal -= box_to_decimal(b));
    CASE(REAL, a->value.real -= box_to_real(b));
  }
}

#define DBOX(v) { .type = DECIMAL, .value.decimal = v }
#define RBOX(v) { .type = REAL, .value.real = v }

/*
int main(void) {
  Array arr = array_new(5);

  Box box = { .type = DECIMAL, .value = 501 };
  Box box2 = { .type = DECIMAL, .value = 502 };
  array_push(&arr, &box);
  array_push(&arr, &box2);
  printf("%ld\n", array_get(&arr, 0)->value.decimal);
  printf("%ld\n", array_get(&arr, 1)->value.decimal);
  
  array_free(&arr);
  return 0;
}
*/

#define MODE 1
#define N 40

int main(void) {
  i64 sum = 0;

  for (int repetitions = 0; repetitions < 100000; ++repetitions) {
  // for (int repetitions = 0; repetitions < 1; ++repetitions) {
#if MODE == 1
  i64* arr = malloc(10 * sizeof(i64));
  i64 a = 5;
  f64 b = 0.1;
  for (int i = 0; i < N; ++i) {
    a += b;
    b += a;
    sum += a;
    arr[0] = sum;
    arr[1] = a;
    arr[2] = arr[0] - arr[1] - b;
    sum -= arr[2];
  }
  sum += repetitions;
  free(arr);
#else
  Array arr = array_new(10);
  Box a = DBOX(5);
  Box b = RBOX(0.1);
  Box i = DBOX(0);
  while (i.value.decimal < N) {
    box_add(&a, &b);
    box_add(&b, &a);
    sum += a.value.decimal;
    array_set(&arr, 0, &(Box) DBOX(sum));
    array_set(&arr, 1, &a);
    box_sub(array_get(&arr, 0), array_get(&arr, 1));
    box_sub(array_get(&arr, 0), &b);
    array_set(&arr, 2, array_get(&arr, 0));
    sum -= array_get(&arr, 2)->value.decimal;
    i.value.decimal += 1;
  }
  sum += repetitions;
  array_free(&arr);
#endif
  }
  
  printf("sum=%ld\n", sum);
  
  return 0;
}

