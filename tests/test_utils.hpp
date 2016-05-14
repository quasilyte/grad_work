#pragma once

#include <cstdio>

inline int errors_count(int value = -1) {
  static int errors = 0;

  if (-1 == value) {
    return errors;
  } else {
    return errors = value;
  }
}

#define TRUE(COND) \
  if (!(COND)) { \
    throw "not true: {" #COND "}"; \
  }

#define FALSE(COND) \
  if (COND) { \
    throw "not false: {" #COND __LINE__ "}"; \
  }

#define RUN(NAME) \
  try { \
    test_##NAME(); \
    puts(#NAME " passed"); \
  } catch (const char* msg) { \
    errors_count(errors_count() + 1); \
    printf(#NAME " FAILED! %s\n", msg); \
  }

#define FINISH() \
  if (errors_count()) { \
    printf("\tthere was %d errors\n", errors_count()); \
    return 1; \
  } else { \
    puts("\tall tests are passed"); \
    return 0; \
  }
