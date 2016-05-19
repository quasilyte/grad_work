#pragma once

#include "typedefs.hpp"
#include "dt/str_view.hpp"
#include "mn_hash.hpp"
#include <vector>

namespace dt {
  template<class T> class Hlist;
}

template<class T> class dt::Hlist {
public:
  struct Node {
    u64 hashed_key = 0;
    T val;

    Node() = default;
    Node(const StrView& key, T val):
    hashed_key{mn_hash::encode9(key.Data(), key.Len())}, val{val} {}
  };

  void Insert(const StrView& key, T val) {
    nodes.push_back(Node{key, val});
  }

  void Drop(int n) {
    nodes.resize(nodes.size() - n);
  }

  T Find(const StrView& key, int limit) const noexcept {
    auto hashed_key = mn_hash::encode9(key.Data(), key.Len());

    auto end = nodes.rend() - (Size() - limit);
    for (auto it = nodes.rbegin(); it != end; ++it) {
      if (it->hashed_key == hashed_key) {
        return it->val;
      }
    }

    return T{};
  }

  T Find(const StrView &key) const noexcept {
    return Find(key, Size());
  }

  uint Size() const noexcept {
    return nodes.size();
  }

private:
  std::vector<Node> nodes;
};
