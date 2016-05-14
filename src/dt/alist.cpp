#include "dt/alist.hpp"

#include "sym/type.hpp"

using namespace dt;

template<class T>
Alist<T>::Node::Node(const StrView& key, T val):
key{key}, val{val} {}

template<class T>
void Alist<T>::Insert(const StrView& key, T val) {
  nodes.push_back(Node{key, val});
}

template<class T>
void Alist<T>::Drop(int n) {
  nodes.resize(nodes.size() - n);
}

template<class T>
uint Alist<T>::Size() const noexcept {
  return nodes.size();
}

template<class T>
T Alist<T>::Find(const StrView& key, int limit) const noexcept {
  auto end = nodes.rend() - (Size() - limit);
  for (auto it = nodes.rbegin(); it != end; ++it) {
    if (it->key == key) {
      return it->val;
    }
  }

  return T{};
}

template<class T>
T Alist<T>::Find(const StrView& key) const noexcept {
  return Find(key, Size());
}

template class dt::Alist<i32>; // For tests
template class dt::Alist<sym::Type*>;
