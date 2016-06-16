#pragma once

#include <cstdio>

struct FailedCase {
  const char* case_name;
  const char* msg;
};

inline int errors_count(int value = -1) {
  static int errors = 0;

  if (-1 == value) {
    return errors;
  } else {
    return errors = value;
  }
}

template<class LAMBDA>
void test_case(const char* name, LAMBDA code) {
  try {
    code();
  } catch (const char* msg) {
    throw FailedCase{name, msg};
  }
}

#define THROWS(EXPR) \
  try { \
    EXPR; \
    throw "not throws: {" #EXPR "}"; \
  } catch (...) {}

#define TRUE(COND) \
  if (!(COND)) { \
    throw "not true: {" #COND "}"; \
  }

#define FALSE(COND) \
  if (COND) { \
    throw "not false: {" #COND "}"; \
  }

#define RUN(NAME) \
  try { \
    test_##NAME(); \
    puts(#NAME " passed"); \
  } catch (const char* msg) { \
    errors_count(errors_count() + 1); \
    printf(#NAME " FAILED! %s\n", msg); \
  } catch (FailedCase e) { \
    errors_count(errors_count() + 1); \
    printf(#NAME " FAILED at %s! %s\n", e.case_name, e.msg); \
  }

#define FINISH() \
  if (errors_count()) { \
    printf("\tthere was %d errors\n", errors_count()); \
    return 1; \
  } else { \
    puts("\tall tests are passed"); \
    return 0; \
  }
