#pragma once

#include "typedefs.hpp"
#include "dt/str_view.hpp"
#include "djb2_hash.hpp"
#include <unordered_map>

namespace dt {
  template<class T> class Dict;
  template<class T> class DictIter;
}

template<class T> class dt::Dict {
public:
  typedef std::unordered_map<StrView, T> Bag;

  auto Iter() const noexcept -> const dt::DictIter<T>;

  void Put(const char* key, T value);
  void Put(const char* key, u32 key_len, T value);
  void Put(StrView key, T value);

  const T& Get(const char* key);
  const T& Get(const char* key, u32 key_len);
  const T& Get(StrView key);

  T Find(StrView key);

  T& GetMut(const char* key);
  T& GetMut(const char* key, u32 key_len);
  T& GetMut(StrView key);

  i32 Size() const noexcept;

private:
  Bag bag;
};

template<> struct std::hash<dt::StrView> {
  usize operator()(const dt::StrView& key) const {
    return djb2_hash::encode(key.Data(), key.Len());
  }
};

template<class T> class dt::DictIter {
public:
  typename Dict<T>::Bag::const_iterator begin() const;
  typename Dict<T>::Bag::const_iterator end() const;

  DictIter(const typename Dict<T>::Bag&);

private:
  const typename Dict<T>::Bag& bag;
};
