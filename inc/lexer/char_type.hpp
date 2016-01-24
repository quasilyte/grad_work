#pragma once

#define SPACE_BITMASK \
  ((1LL << 0x0009) |  \
   (1LL << 0x000A) |  \
   (1LL << 0x000B) |  \
   (1LL << 0x000C) |  \
   (1LL << 0x000D) |  \
   (1LL << 0x0020))

// \s
inline bool is_space(char ch) {
  return (SPACE_BITMASK >> ch) & 1L;
}

// \S
inline bool not_space(char ch) {
  return 0 == ((SPACE_BITMASK >> ch) & 1L);
}

// [a-zA-Z]
inline bool is_alpha(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// \d
inline bool is_digit(char ch) {
  return ch >= '0' && ch <= '9';
}

// \w
inline bool is_word(char ch) {
  return is_alpha(ch) || is_digit(ch) || ch == '_';
}

#define NONPRINTABLE_CASE		                   	\
  case 1: case 2: case 3: case 4:	            	\
  case 5: case 6: case 7: case 8: case 9:	      \
  case 10: case 11: case 12: case 13: case 14:	\
  case 15: case 16: case 17: case 18: case 19:	\
  case 20: case 21: case 22: case 23: case 24:	\
  case 25: case 26: case 27: case 28: case 29:	\
  case 30: case 31: case 32

#define UCASE_CASE			                	\
  case 'A': case 'B': case 'C': case 'D':	\
  case 'E': case 'F': case 'G': case 'H':	\
  case 'I': case 'J': case 'K': case 'L':	\
  case 'M': case 'N': case 'O': case 'P':	\
  case 'Q': case 'R': case 'S': case 'T':	\
  case 'U': case 'V': case 'W': case 'X':	\
  case 'Y': case 'Z'

#define LCASE_CASE				\
  case 'a': case 'b': case 'c': case 'd':	\
  case 'e': case 'f': case 'g': case 'h':	\
  case 'i': case 'j': case 'k': case 'l':	\
  case 'm': case 'n': case 'o': case 'p':	\
  case 'q': case 'r': case 's': case 't':	\
  case 'u': case 'v': case 'w': case 'x':	\
  case 'y': case 'z'

#define DIGIT_CASE				\
  case '0': case '1': case '2': case '3':	\
  case '4': case '5': case '6': case '7':	\
  case '8': case '9'

#undef SPACE_BITMASK
