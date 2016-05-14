#include "test_dt/suit.hpp"

#include "dt/alist.hpp"
#include "dt/hlist.hpp"
#include "test_utils.hpp"

int main() {
  RUN(list<dt::Alist>);
  RUN(list<dt::Hlist>);

  FINISH(0);
}
