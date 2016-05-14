#include "dt/alist.hpp"

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
T Alist<T>::Find(const StrView& key) const noexcept {
  for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
    if (it->key == key) {
      return it->val;
    }
  }

  return T{};
}

template class dt::Alist<i32>;
