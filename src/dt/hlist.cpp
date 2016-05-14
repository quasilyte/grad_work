#include "dt/hlist.hpp"

#include "mn_hash.hpp"
#include "dev_assert.hpp"

using namespace dt;

template<class T>
Hlist<T>::Node::Node(const StrView& key, T val):
hashed_key{mn_hash::encode9(key.Data(), key.Len())}, val{val} {}

template<class T>
void Hlist<T>::Insert(const StrView& key, T val) {
  nodes.push_back(Node{key, val});
}

template<class T>
void Hlist<T>::Drop(int n) {
  nodes.resize(nodes.size() - n);
}

template<class T>
T Hlist<T>::Find(const StrView& key) const noexcept {
  auto hashed_key = mn_hash::encode9(key.Data(), key.Len());

  for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
    if (it->hashed_key == hashed_key) {
      return it->val;
    }
  }

  return T{};
}

template class dt::Hlist<i32>;
