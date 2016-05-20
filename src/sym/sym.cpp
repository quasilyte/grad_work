#include "sym/sym.hpp"

#include "fmt/uint.hpp"

// 0 1 2 3 4 5 6 7 8 9
// 01 12 23 34 45 56 67 78 89
// 012 123 234 345 456 567 678 789
// 0123 ...
// ...
// 0123456789
dt::StrView sym::gen_suffix(u32 idx) {
  static const char alphabet[] = "0123456789";

  switch (idx) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9: return dt::StrView{alphabet + idx, 1};
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:
  case 16:
  case 17:
  case 18: return dt::StrView{alphabet + idx - 10, 2};
  case 19:
  case 20:
  case 21:
  case 22:
  case 23:
  case 24:
  case 25:
  case 26: return dt::StrView{alphabet + idx - 19, 3};
  case 27:
  case 28:
  case 29:
  case 30:
  case 31:
  case 32:
  case 33: return dt::StrView{alphabet + idx - 27, 4};
  case 34:
  case 35:
  case 36:
  case 37:
  case 38:
  case 39: return dt::StrView{alphabet + idx - 34, 5};
  case 40:
  case 41:
  case 42:
  case 43:
  case 44: return dt::StrView{alphabet + idx - 40, 6};
  case 45:
  case 46:
  case 47:
  case 48: return dt::StrView{alphabet + idx - 45, 7};
  case 49:
  case 50:
  case 51: return dt::StrView{alphabet + idx - 49, 8};
  case 52:
  case 53: return dt::StrView{alphabet + idx - 52, 9};
  case 54: return dt::StrView{alphabet, 10};
  default:
    throw "suffix out of range";
  }
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
