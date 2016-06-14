#pragma once

#include <dt/str_view.hpp>
#include <djb2_hash.hpp>
#include <deps/cxx/unordered_map.hpp>

namespace sym {
  struct QualifiedId;
}

struct sym::QualifiedId {
  QualifiedId(dt::StrView pkg_name, dt::StrView identifier);

  bool operator==(const QualifiedId& other) const;

  dt::StrView pkg_name;
  dt::StrView identifier;
};

template<> struct std::hash<dt::QualifiedId> {
  usize operator()(const sym::QualifiedId& key) const {
    return (
      djb2_hash::encode(key.pkg_name.Data(), key.pkg_name.Len()) +
      djb2_hash::encode(key.identifier.Data(), key.identifier.Len())
    ) / 2;
  }
};
