#include <bench_utils.hpp>
#include <init_utils.hpp>
#include <lex/reader.hpp>
#include <dt/str_view.hpp>
#include <mn_hash.hpp>

#include <dbg/dt.hpp>
#include <deps/cxx/vector.hpp>
#include <deps/cxx/map.hpp>
#include <deps/c/string.hpp>
#include <tuple>

using namespace lex;
using namespace chars;
using namespace dt;

void init() {
  init_char_categories();
}

u64 test_str(int argc) {
  std::vector<const char*> bag = {
    "?23:a",
    "1?3:b",
    "12?:c",
  };
  std::vector<const char*> hits = {
    "?23:a",
    "234:b",
    "133:c",
    "456:d",
    "12?:c"
  };

  u64 score = 0;
  for (int i = 0; i < 500000; ++i) {
    for (int j = 0; j < 5; ++j) {
      for (int k = 0; k < 3; ++k) {
        if (0 == strcmp(bag[k], hits[j])) {
          score += k;
        }
      }
    }
  }
  return score;
}

u64 test_vec(int argc) {
  std::vector<std::vector<int>> bag = {
    {1, 2},
    {1, 1},
    {1, 2},
  };
  std::vector<std::vector<int>> hits = {
    {1, 2},
    {2, 3},
    {1, 3},
    {4, 5},
    {1, 2},
  };

  u64 score = 0;
  for (int i = 0; i < 500000; ++i) {
    for (int j = 0; j < 5; ++j) {
      for (int k = 0; k < 3; ++k) {
        if (bag[k] == hits[j]) {
          score += k;
        }
      }
    }
  }
  return score;
}

void test(int argc) {
  StrView input{
    R"code(
        (var x int = 40)
        (var foo float = 423 + 4 + 5)
        (var barbaz string = ( "54" + "35tuf" ) )
        (var long_ident_name x = (pretty long expr here) )
        (var x int = 40)
        (var  foo float = 423 + 4 + 5
        var barbaz string = ( "54" + "35tuf" )
        var long_ident_name x = (pretty long expr here) */ )
        (var foo float = 423 + 4 + 5
        var barbaz string*/ = ( "54" + "35tuf" )
        var x int = 40)
        (var x int = 40
        var x int = 40)
        (var long_ident_name x = (pretty long expr here)
        var foo float = 423 + 4 + 5)
        (var barbaz string = ( "54" + "35tuf" )
        var x int = 40
        var x int = 40)
  )code"};


  auto b = bench_run("vec", 5, [&](int n) {
    return test_vec(argc);
  });

  auto a = bench_run("str", 5, [&](int n) {
    return test_str(argc);
  });

  RunResults::Compare(a, b);

  /*
  RunResults::Compare(
        bench_run("elegant", 5, [&](int n) {
          Reader reader{input};
          return elegant(reader);
        }),
        bench_run("parseR", 5, [&](int n) {
          return 0;
        })
  );*/
}

int main(int argc, char* argv[]) {
  init();

  test(argc);

  /*
  StrView input{R"code(
    this is input from which lexer should collect m9 hashed values
    it is okay that some of words can exceed the limit of nine characters
  )code"};

  RunResults::Compare(
    bench_run("read + m9", 5, [&](int n){
      u64 score = 0;
      int repeats = n + 150000;

      for (int i = 0; i < repeats; ++i) {
        Reader rd{input};

        while (rd.Skip()->CanRead()) {
          auto word = rd.Read(C_IDENT);
          if (word.Len() < 10) {
            score += mn_hash::encode9(word.Data(), word.Len());
          }
        }
      }

      return (score / ((n + 1) * 1000)) / repeats;
    }),
    bench_run("read_m9", 5, [&](int n){
      u64 score = 0;
      int repeats = n + 150000;

      for (int i = 0; i < repeats; ++i) {
        Reader rd{input};

        while (rd.Skip()->CanRead()) {
          score += rd.ReadM9(C_IDENT);
        }
      }

      return (score / ((n + 1) * 1000)) / repeats;
    })
  );
  */
}
