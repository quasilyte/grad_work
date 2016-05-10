#include "cc/classifier.hpp"

#include "mn_hash.hpp"
#include <cstring>

using namespace cc;
using namespace lex;

TopLevel Classifier::Run(const char* input_cstr) {
  Classifier self{input_cstr};
  return self.Classify();
}

TopLevel Classifier::Run(const char* input, usize input_len) {
  Classifier self{input, input_len};
  return self.Classify();
}

Classifier::Classifier(const char* input_cstr):
toks{TokenStream{input_cstr, std::strlen(input_cstr)}} {}

Classifier::Classifier(const char* input, usize input_len):
toks{TokenStream{input, input_len}} {}

TopLevel Classifier::Classify() {
  while (!toks.NextToken().IsEof()) {

    auto tok = toks.CurrentToken();

    if ('#' == *tok.Val() && tok.IsList()) {
      ClassifyDirective(tok);
    } else {
      result.exprs.push_back(tok);
    }
  }

  return result;
}

void Classifier::ClassifyDirective(const lex::Token& directive) {
  using namespace mn_hash;

  TokenStream list{directive};

  auto name = list.NextToken();
  // Skip '#' char during hashing (hence +1)
  auto name_hash = encode9(name.Val() + 1, name.Len() - 1);

  switch (name_hash) {
  case encode9("def"): ClassifyDef(list);
  case encode9(";"): return; // Comment lists are just ignored

  default:
    throw "unknown directive";
  }
}

void Classifier::ClassifyDef(TokenStream toks) {
  auto toks_copy = toks;
  auto target = toks.NextToken();

  if (target.IsList()) {
    result.funcs.push_back(toks_copy);
  } else if (target.IsWord()) {
    result.globals.push_back(toks_copy);
  } else {
    throw "only {word, list} are valid targets for #def";
  }
}
