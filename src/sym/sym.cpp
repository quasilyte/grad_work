#include "sym/sym.hpp"

dt::StrView sym::gen_suffix(uint idx) {
  // Up to 2015 unique identifiers
  if (idx > MAX_UNIQ_SUFFIXES) {
    throw "gen_suffix: idx overflows MAX_UNIQ_SUFFIXES";
  }

  static const char alphabet[] =
    "0123456789"                 // 10
    "abcdefghijklmnopqrstuvwxyz" // 26
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ" // 26
    "_";                         // 1
  static const uint alphabet_size = 10 + 26 + 26 + 1;

  u32 len = 1;

  for (uint i = alphabet_size; idx >= i; --i) {
    idx -= i;
    len += 1;
  }

  return dt::StrView{alphabet + idx, len};
}

const char* sym::mangle(char ch) {
  static const char* mangled[] = {
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "0", /* ! */
    "", /* " */
    "2", /* # */
    "3", /* $ */
    "4", /* % */
    "5", /* & */
    "6", /* ' */
    "", /* ( */
    "", /* ) */
    "7", /* * */
    "8", /* + */
    "9", /* , */
    "10", /* - */
    "11", /* . */
    "12", /* / */
    "_0", /* 0 */
    "_1", /* 1 */
    "_2", /* 2 */
    "_3", /* 3 */
    "_4", /* 4 */
    "_5", /* 5 */
    "_6", /* 6 */
    "_7", /* 7 */
    "_8", /* 8 */
    "_9", /* 9 */
    "13", /* : */
    "14", /* ; */
    "15", /* < */
    "16", /* = */
    "17", /* > */
    "18", /* ? */
    "19", /* @ */
    "A", /* A */
    "B", /* B */
    "C", /* C */
    "D", /* D */
    "E", /* E */
    "F", /* F */
    "G", /* G */
    "H", /* H */
    "I", /* I */
    "J", /* J */
    "K", /* K */
    "L", /* L */
    "M", /* M */
    "N", /* N */
    "O", /* O */
    "P", /* P */
    "Q", /* Q */
    "R", /* R */
    "S", /* S */
    "T", /* T */
    "U", /* U */
    "V", /* V */
    "W", /* W */
    "X", /* X */
    "Y", /* Y */
    "Z", /* Z */
    "20", /* [ */
    "21", /* \ */
    "22", /* ] */
    "23", /* ^ */
    "24", /* _ */
    "25", /* ` */
    "a", /* a */
    "b", /* b */
    "c", /* c */
    "d", /* d */
    "e", /* e */
    "f", /* f */
    "g", /* g */
    "h", /* h */
    "i", /* i */
    "j", /* j */
    "k", /* k */
    "l", /* l */
    "m", /* m */
    "n", /* n */
    "o", /* o */
    "p", /* p */
    "q", /* q */
    "r", /* r */
    "s", /* s */
    "t", /* t */
    "u", /* u */
    "v", /* v */
    "w", /* w */
    "x", /* x */
    "y", /* y */
    "z", /* z */
    "26", /* { */
    "27", /* | */
    "28", /* } */
    "29", /* ~ */
  };

  return mangled[static_cast<int>(ch)];
}
