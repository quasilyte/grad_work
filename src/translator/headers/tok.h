#ifndef HEADERS_TOK_
#define HEADERS_TOK_

#define PLUS_M4 43
#define PLUS2_M4 5547
#define MINUS_M4 45
#define MINUS2_M4 5805
#define EQ_M4 61
#define EQ2_M4 7869
#define EQ3_M4 1007293
#define ARROW_M4 5805
#define SINGLE_QUOTE_M4 39
#define BACK_QUOTE_M4 96
#define DOT_M4 46
#define COMMA_M4 44
#define STAR_M4 42
#define SLASH_M4 47
#define BANG_M4 33
#define AMP_M4 38
#define AMP2_M4 4902

#define M4(key) key##_M4

enum TokTag {
  PLUS, PLUS2, // + ++
  MINUS, MINUS2, // - --
  LPAREN, RPAREN, // ( )
  LBRACE, RBRACE, // { }
  LBRACKET, RBRACKET, // [ ]
  EQ, EQ2, EQ3, // = == ===
  ARROW, // ->
  SINGLE_QUOTE, BACK_QUOTE, // ' `
  DOT, // .
  COMMA, // ,
  STAR, // *
  SLASH, // /
  BANG, // !
  AMP, AMP2, // & &&
  WORD, 
  DECIMAL,
};
typedef enum TokTag TokTag;

deftype(Tok) {
  TokTag tag;
  char* val;
};

#endif
