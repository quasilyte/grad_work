struct IdRule {} ID;
struct ExprRule {} EXPR;
struct TermRule {
  const char* term;
};

void parse_one(Reader* r, int*, dt::StrView*, TermRule rule) {
  r->Skip()->MustConsume(rule.term);
}

void parse_one(Reader* r, int* i, dt::StrView* result, ExprRule) {
  result[*i] = r->Skip()->ReadUntil('\n');
  *i = *i + 1;
}

void parse_one(Reader* r, int* i, dt::StrView* result, IdRule) {
  result[*i] = r->Skip()->Read(C_IDENT);
  *i = *i + 1;
}

template<class T>
void parse_list(Reader *r, int *i, StrView *result, T rule) {
  parse_one(r, i, result, rule);
}

template<class T, class... RULES>
void parse_list(Reader* r, int* i, dt::StrView* result, T rule, RULES... rules) {
  parse_one(r, i, result, rule);
  parse_list(r, i, result, rules...);
}

template<int N, class... RULES>
auto parse(Reader* r, RULES... rules) {
  std::array<dt::StrView, N> elts;

  int i = 0;
  parse_list(r, &i, elts.begin(), rules...);

  return elts;
}

// parse<3>(&rd, TermRule{"var"}, ID, ID, TermRule{"="}, EXPR)
// parse<2>(&rd, TermRule{"var"}, ID, TermRule{"="}, EXPR)
