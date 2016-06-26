#pragma once

#include <typedefs.hpp>
#include <chrono>
#include <limits>
#include <cstdio>

using namespace std::chrono;

struct RunResults {
  const char* name;
  u64 shortest;
  u64 average;
  u64 longest;
  u64 result;
  int n;

  void PrintDiffLine(const char* x_name, const char* metric, u64 x, u64 y) const {
    printf("\t{%s} %s: -%lu ms (x%.2f faster)\n",
      x_name, metric, y - x, static_cast<float>(y) / x
    );
  }

  static void Compare(const RunResults& a, const RunResults& b) {
    a.Print();
    b.Print();
    a.Compare(b);
  }

  void Compare(const RunResults& other) const {
    printf(
      "{%s} & {%s} results are {%s}\n",
      name, other.name,
      result == other.result ? "same" : "different"
    );

    if (shortest < other.shortest) {
      PrintDiffLine(name, "best", shortest, other.shortest);
    } else {
      PrintDiffLine(other.name, "best", other.shortest, shortest);
    }

    if (average < other.average) {
      PrintDiffLine(name, "avg", average, other.average);
    } else {
      PrintDiffLine(other.name, "avg", other.average, average);
    }

    if (longest < other.longest) {
      PrintDiffLine(name, "worst", longest, other.longest);
    } else {
      PrintDiffLine(other.name, "worst", other.longest, longest);
    }
  }

  void Print() const {
    printf(
      "{%s} was executed for {%d} times: {\n"
      "\tbest:\t%lu\n"
      "\tavg:\t%lu\n"
      "\tworst:\t%lu\n"
      "\tsum:\t%lu\n"
      "}\n",
      name, n,
      shortest,
      average,
      longest,
      result
    );
  }
};

template<class LAMBDA>
RunResults bench_run(const char* name, int n, LAMBDA code) {
  printf("bench_run(\"%s\", %d, ...)\n", name, n);

  u64 shortest_elapsed = std::numeric_limits<u64>::max();
  u64 longest_elapsed = 0;
  u64 total_elapsed = 0;
  u64 total_result = 0;

  for (int i = 0; i < n; ++i) {
    auto timestamp1 = high_resolution_clock::now();
    total_result += code(i);
    auto timestamp2 = high_resolution_clock::now();
    u64 elapsed = duration_cast<milliseconds>(timestamp2 - timestamp1).count();

    total_elapsed += elapsed;
    if (elapsed < shortest_elapsed) {
      shortest_elapsed = elapsed;
    }
    if (elapsed > longest_elapsed) {
      longest_elapsed = elapsed;
    }
  }

  return RunResults{
    name,
    shortest_elapsed,
    total_elapsed / n,
    longest_elapsed,
    total_result,
    n
  };
}
