#include <lex/num_tagger.hpp>

#include <chars/categories.hpp>
#include <lex/reader.hpp>

using namespace lex;
using namespace chars;

u32 NumTagger::Run(Reader* reader) {
  if (!reader->TryConsume(DIGITS)) {
    return MALFORMED;
  }

  if (reader->TryConsume('.')) {
    return reader->TryConsume(DIGITS) ? REAL : MALFORMED;
  } else {
    return INT;
  }
}
