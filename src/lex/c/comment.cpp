#include <lex/c/comment.hpp>

#include <lex/reader.hpp>

using namespace lex;
using namespace c_lex;

void Comment::Skip(Reader* reader) {
  if ('/' == reader->PeekCurrent()) {
    switch (reader->PeekNext()) {
    case '/':
      reader->DoSkipLine();
      return;

    case '*':
      for (;;) {
        reader->DoSkip(2);
        reader->DoSkipUntil('*');
        if ('/' == reader->PeekNext()) {
          return;
        }
      }
    }
  }
}

