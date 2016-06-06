#pragma once

#include <typedefs.hpp>
#include <dt/str_view.hpp>
#include <deps/cxx/vector.hpp>

namespace dt {
  template<class T> class Alist;
}

template<class T> class dt::Alist {
public:
  struct Node {
    StrView key;
    T val;

    Node() = default;
    Node(const StrView& key, T val): key{key}, val{val} {}
  };

  void Insert(const StrView& key, T val) {
    nodes.push_back(Node{key, val});
  }

  void Drop(int n) {
    nodes.resize(nodes.size() - n);
  }

  T Find(const StrView& key, int limit) const noexcept {
    auto end = nodes.rend() - (Size() - limit);
    for (auto it = nodes.rbegin(); it != end; ++it) {
      if (it->key == key) {
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

