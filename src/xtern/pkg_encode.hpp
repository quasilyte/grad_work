#pragma once

#include <sym/type.hpp>
#include <sym/typedefs.hpp>
#include <sym/fn.hpp>

namespace dt {
  class StrView;
}

namespace io {
  class FileWriter;
}

namespace xtern {
# define StrView dt::StrView
# define Type sym::Type
# define ParamList sym::ParamList
# define FileWriter io::FileWriter

  void encode_byte(FileWriter& fw, char byte);
  void encode_type(FileWriter& fw, Type type);
  void encode_string(FileWriter& fw, const StrView& str);

  // void encode_fn(FileWriter&, StrView name, Type ret_type, const ParamList&);
  void encode_fn(FileWriter&, const sym::MonoFn&);

  void decode_modules(const char* data);

# undef StrView
# undef Type
# undef ParamList
# undef FileWriter
}
