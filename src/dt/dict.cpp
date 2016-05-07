#include "dt/dict.hpp"

using namespace dt;

#include "dt/dict.hpp"

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
T& dt::Dict<T>::Get(const char *key) {
  return bag[StrView{key}];
}

template<class T>
T& dt::Dict<T>::Get(const char* key, u32 key_len) {
  return bag[StrView{key, key_len}];
}

template<class T>
T& dt::Dict<T>::Get(StrView key) {
  return bag[key];
}

template class dt::Dict<int>;
