#include <dt/dict.hpp>

#include <sym/fn.hpp>
#include <sym/global.hpp>
#include <sym/struct.hpp>

using namespace dt;

template<class T>
auto dt::Dict<T>::Iter() const noexcept -> const DictIter<T> {
  return DictIter<T>{bag};
}

template<class T>
void dt::Dict<T>::Put(const char *key, T value) {
  bag[StrView{key}] = value;
}

template<class T>
void dt::Dict<T>::Put(const char *key, u32 key_len, T value) {
  bag[StrView{key, key_len}] = value;
}

template<class T>
void dt::Dict<T>::Put(StrView key, T value) {
  bag[key] = value;
}

template<class T>
const T& dt::Dict<T>::Get(const char *key) {
  return bag[StrView{key}];
}

template<class T>
const T& dt::Dict<T>::Get(const char* key, u32 key_len) {
  return bag[StrView{key, key_len}];
}

template<class T>
const T& dt::Dict<T>::Get(StrView key) {
  return bag[key];
}

template<class T>
T dt::Dict<T>::Find(StrView key) const {
  auto it = bag.find(key);

  if (it == bag.end()) {
    return T{};
  } else {
    return it->second;
  }
}

template<class T>
T& dt::Dict<T>::GetMut(const char *key) {
  return bag[StrView{key}];
}

template<class T>
T& dt::Dict<T>::GetMut(const char* key, u32 key_len) {
  return bag[StrView{key, key_len}];
}

template<class T>
T& dt::Dict<T>::GetMut(StrView key) {
  return bag[key];
}

template<class T>
u32 dt::Dict<T>::Size() const noexcept {
  return bag.size();
}

template class dt::Dict<sym::Struct*>;
template class dt::Dict<sym::Type>;
template class dt::Dict<sym::MultiFn*>;
template class dt::Dict<sym::MonoFn*>;
template class dt::Dict<sym::Global*>;

template<class T>
dt::DictIter<T>::DictIter(const typename Dict<T>::Bag& bag): bag{bag} {}

template<class T>
typename Dict<T>::Bag::const_iterator DictIter<T>::begin() const {
  return bag.begin();
}

template<class T>
typename Dict<T>::Bag::const_iterator DictIter<T>::end() const {
  return bag.end();
}

template class dt::DictIter<sym::MultiFn*>;
