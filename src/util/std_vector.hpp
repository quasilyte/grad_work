#pragma once

#include <vector>

namespace util {
  template<class IN, class OUT>
  std::vector<OUT> map(std::vector<IN> elems, OUT(*fn)(IN)); 
}

template<class IN, class OUT>
std::vector<OUT> util::map(std::vector<IN> elems, OUT(*fn)(IN)) {
  std::vector<OUT> result;
  result.reserve(elems.size());

  for (IN elem : elems) {
    result.push_back(fn(elem));
  }

  return result;
}
