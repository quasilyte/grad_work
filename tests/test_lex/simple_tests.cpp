#include <test_lex/suite.hpp>

#include <test_utils.hpp>
#include <lex/reader.hpp>
#include <lex/c/comment.hpp>
#include <chars/categories.hpp>
#include <mn_hash.hpp>
#include <macro/or.hpp>
#include <err/lex_errors.hpp>
#include <err/fatal.hpp>

using namespace chars;
using namespace dt;

class Reader: public lex::Reader {
public:
  using lex::Reader::Reader;

  Reader* Skip(chars::Alphabet to_skip = chars::SPACES) {
    DoSkip(to_skip);
    return this;
  }

  Reader* SkipUntil(char c) {
    DoSkipUntil(c);
    return this;
  }

  dt::StrView ReadGroup(char open, char close) {
    return lex::Reader::ReadGroup<c_lex::Comment>(open, close);
  }
};

dt::StrView read_expr(Reader* reader) {
  return '(' == reader->PeekCurrent()
      ? reader->ReadGroup('(', ')')
      : reader->ReadLine();
}

void test_sanity() {
  test_case("Empty reader", [](){
    Reader rd1;
    FALSE(rd1.CanRead());
    Reader rd2{""}; // Same as above
    FALSE(rd2.CanRead());
  });

  test_case("Non-empty reader", [](){
    Reader rd{"$"};
    TRUE(rd.CanRead());
  });
}

void test_skip_and_peek() {
  test_case("Skip spaces and peek current", [](){
    Reader rd{"  \t 1"};
    TRUE('1' == rd.Skip(SPACES)->PeekCurrent());
    rd.DoSkip(SPACES); // Should not move the cursor
    TRUE('1' == rd.PeekCurrent());
  });

  test_case("Skip by alphabet", [](){
    Reader rd{"abc50"};
    TRUE('5' == rd.Skip(LETTERS)->PeekCurrent());
  });

  test_case("Skip until", [](){
    Reader rd{"abc50"};
    TRUE('5' == rd.SkipUntil('5')->PeekCurrent())
  });

  test_case("Skip n", [](){
    Reader rd{"1234"};
    rd.DoSkip(1);
    TRUE('2' == rd.PeekCurrent());
    TRUE('1' == rd.PeekPrev());
    TRUE('3' == rd.PeekNext());
    rd.DoSkip(2);
    TRUE('4' == rd.PeekCurrent());
  });
}
#include<dbg/dt.hpp>
void test_basic_read() {
  test_case("Read C ident", [](){
    Reader rd{"\tc_ident777()\n 400 "};
    TRUE(StrView{"c_ident777"} == rd.Skip()->Read(C_IDENT));
    TRUE(rd.Read(C_IDENT).IsEmpty());
  });

  test_case("Read until", [](){
    Reader rd1{"foo bar\n%baz"};
    TRUE(StrView{"foo bar\n"} == rd1.ReadUntil('%'));
    Reader rd2{"foo bar"};
    rd2.ReadUntil('%');
    FALSE(rd2.CanRead()); // Can not read, cursor is at EOF
  });

  test_case("Ream m9", [](){
    using mn_hash::operator "" _m9;
    Reader rd{"foobar x003$"};
    auto foobar = rd.ReadM9(LETTERS);
    auto x003 = rd.Skip()->ReadM9(C_IDENT);
    auto nil = rd.Skip()->ReadM9(C_IDENT);
    TRUE("foobar"_m9 == foobar && "x003"_m9 == x003 && 0 == nil);
    TRUE('$' == rd.PeekCurrent());
  });


  test_case("read line", [](){
    Reader rd1{"line1\nline2\n$"};
    TRUE(StrView{"line1"} == rd1.ReadLine());
    TRUE('l' == rd1.PeekCurrent());
    TRUE(StrView{"line2"} == rd1.ReadLine());
    TRUE('$' == rd1.PeekCurrent());

    Reader rd2{"$"};
    THROWS(rd2.ReadLine(), err::Fatal);
    FALSE(rd2.CanRead());

    const char* input = "abc$\n";
    Reader rd3{StrView{input, 4}};
    Reader rd4{StrView{input, 5}};
    THROWS(rd3.ReadLine(), err::Fatal);
    TRUE(StrView{"abc$"} == rd4.ReadLine());
    FALSE(rd3.CanRead() || rd4.CanRead());
  });

  test_case("read expr", [](){
    Reader rd{"1+1\n(1\n+\n2)$()$"};
    auto expr1 = read_expr(&rd);
    TRUE(StrView{"1+1"} == expr1);
    auto expr2 = read_expr(&rd);
    TRUE(StrView{"1\n+\n2"} == expr2);
    TRUE(rd.TryConsume('$'));
    TRUE(rd.ReadGroup('(', ')'));
    TRUE(rd.TryConsume('$'));
  });
}

void test_advanced_read() {
  /*
  test_case("read empty group", [](){
    Reader rd1{"$"};
    THROWS(rd1.ReadGroup('(', ')'), err::UnbalancedGroup);
    TRUE('$' == rd1.PeekCurrent());

    Reader rd2{"(a(b)"};
    THROWS(rd2.ReadGroup('(', ')'), err::UnbalancedGroup);
  });

  test_case("read empty literal", [](){
    Reader rd1{"$"};
    THROWS(rd1.ReadLiteral('"'), err::UnclosedLiteral);
    TRUE('$' == rd1.PeekCurrent());

    Reader rd2{"'hello"};
    THROWS(rd2.ReadLiteral('\''), err::UnclosedLiteral);
  });
  */

  test_case("read literal", [](){
    Reader rd1{"'x \\' \\' y'$"};
    TRUE(StrView{"x \\' \\' y"} == rd1.ReadLiteral('\''));
    TRUE('$' == rd1.PeekCurrent());
  });

  test_case("read balanced group", [](){
    Reader rd{"(define (id x) x)${1 \"{{\" 2}$"};

    TRUE(StrView{"define (id x) x"} == rd.ReadGroup('(', ')'));
    TRUE(rd.TryConsume('$'));
    TRUE(StrView{"1 \"{{\" 2"} == rd.ReadGroup('{', '}'));
    TRUE('$' == rd.PeekCurrent());
  });

  test_case("read combined", [](){
    Reader rd{"('1' + '2')$('1' + ('2') + '3')$"};

    TRUE(StrView{"'1' + '2'"} == rd.ReadGroup('(', ')'));
    TRUE(rd.TryConsume('$'));
    TRUE(StrView{"'1' + ('2') + '3'"} == rd.ReadGroup('(', ')'));
    TRUE(rd.TryConsume('$'));
  });
}

void test_consuming_functions() {
  test_case("Consume char", [](){
    Reader rd{"a$"};
    FALSE(rd.TryConsume('b'));
    TRUE('a' == rd.PeekCurrent());
    TRUE(rd.TryConsume('a'));
    TRUE('$' == rd.PeekCurrent());
  });

  test_case("Consume string", [](){
    Reader rd{"for$"};
    FALSE(rd.TryConsume("if"));
    TRUE('f' == rd.PeekCurrent());
    TRUE(rd.TryConsume("for"));
    TRUE('$' == rd.PeekCurrent());
  });
}

void test_looping() {
  Reader rd{" aa bb cc dd "};
  int token_count = 0;
  int total_len = 0;

  while (rd.Skip()->CanRead()) {
    token_count += 1;
    total_len += rd.Read(LETTERS).Len();
  }

  TRUE(4 == token_count);
  TRUE(8 == total_len);
}

void test_comment_skip() {
  test_case("single line comments", [](){
    Reader rd{"(a//)\nb)[a// ]\nb]{a //}\n b}$"};
    TRUE(StrView{"a//)\nb"} == rd.ReadGroup('(', ')'));
    TRUE(StrView{"a// ]\nb"} == rd.ReadGroup('[', ']'));
    TRUE(StrView{"a //}\n b"} == rd.ReadGroup('{', '}'));
    TRUE(rd.TryConsume('$'));
  });

  test_case("multi line comments", [](){
    Reader rd1{"(a/*)*/b)[a/* ] */b]{a /*}*/ b}$"};
    TRUE(StrView{"a/*)*/b"} == rd1.ReadGroup('(', ')'));
    TRUE(StrView{"a/* ] */b"} == rd1.ReadGroup('[', ']'));
    TRUE(StrView{"a /*}*/ b"} == rd1.ReadGroup('{', '}'));
    TRUE(rd1.TryConsume('$'));

    Reader rd2{"(a/*\n\n*/b)$"};
    TRUE(StrView{"a/*\n\n*/b"} == rd2.ReadGroup('(', ')'));
    TRUE(rd2.TryConsume('$'));

    Reader rd3{"(/* */)(/*  */)"};
    TRUE(StrView{"/* */"} == rd3.ReadGroup('(', ')'));
    TRUE(StrView{"/*  */"} == rd3.ReadGroup('(', ')'));
  });

  test_case("empty multi line comments", [](){
    Reader rd{"(/**/)$"};
    TRUE(StrView{"/**/"} == rd.ReadGroup('(', ')'));
    TRUE(rd.TryConsume('$'));
  });
}
