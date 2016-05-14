#include "test_dt/suit.hpp"

#include "test_utils.hpp"

namespace dt {
  template<class T> class Alist;
  template<class T> class Hlist;
}

int main() {
  RUN(list<dt::Alist>);
  RUN(list<dt::Hlist>);

  FINISH();
}
