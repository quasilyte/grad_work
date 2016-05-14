#pragma once

#include <cstdio>

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
    puts(#NAME "passed!"); \
  } catch (const char* msg) { \
    printf(#NAME " failed! %s\n", msg); \
  }

#define FINISH(CODE) puts("\tall tests are passed"); return CODE;
