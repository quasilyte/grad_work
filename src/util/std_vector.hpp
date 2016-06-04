#pragma once

#include <vector>

namespace util {
  template<class IN, class OUT>
  std::vector<OUT> map(std::vector<IN> vec, OUT(*fn)(IN));

  template<class T>
  T pop(std::vector<T>& vec);
}

template<class IN, class OUT>
std::vector<OUT> util::map(std::vector<IN> vec, OUT(*fn)(IN)) {
  std::vector<OUT> result;
  result.reserve(vec.size());

  for (IN elem : vec) {
    result.push_back(fn(elem));
  }

  return result;
}

template<class T>
T util::pop(std::vector<T>& vec) {
  auto elem = vec.back();
  vec.pop_back();

  return elem;
}
