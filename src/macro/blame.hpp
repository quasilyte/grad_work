#pragma once

#include <unit/source.hpp>
#include <deps/c/stdio.hpp>

#define BLAME(FORMAT, LINE_NUMBER_PROVIDER, ...) \
  std::fprintf( \
    stderr, \
    "line %d: " \
    FORMAT \
    "\n", \
    unit::get_line_number(LINE_NUMBER_PROVIDER), \
    __VA_ARGS__ \
  )

// Differs from BLAME in format string. `line` has index-based
// argument, so all format string placeholders ought to be index-based
#define BLAME_INDEXED(FORMAT, LINE_NUMBER_PROVIDER, ...) \
  std::fprintf( \
    stderr, \
    "line %1$d: " \
    FORMAT \
    "\n", \
    unit::get_line_number(LINE_NUMBER_PROVIDER), \
    __VA_ARGS__ \
  )

#define BUF_FMT(BUF) \
  BUF.Len(), \
  BUF.Data()
