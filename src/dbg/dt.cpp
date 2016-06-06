#include <dbg/dt.hpp>

#include <deps/c/stdio.hpp>

void dbg::dump(const dt::StrView& str_view) {
  std::printf(
    "StrView{data: `%.*s`, len: %u}\n",
     str_view.Len(), str_view.Data(),
     str_view.Len()
  );
}
