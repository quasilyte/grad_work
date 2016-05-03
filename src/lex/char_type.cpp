#include "char_type.hpp"

bool lex::is_space(char ch) {
  return ch == ' ' || ch == '\t' || ch == '\n';
}

bool lex::not_space(char ch) {
  return !is_space(ch);
}

bool lex::is_alpha(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool lex::is_digit(char ch) {
  return ch >= '0' && ch <= '9';
}

bool lex::is_word(char ch) {
  return is_alpha(ch) || is_digit(ch) || ch == '_';
}
