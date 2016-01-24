#include <cstdio>
#include <vector>

using namespace std;

int main(void) {
  long score = 0;

  vector<int> vals;
  vals.reserve(20);
  for (int i = 0; i < 20; ++i) vals.push_back(i * i);

  for (size_t i = 1; i < 50000; ++i) {
    vector<char> vecc;
    vecc.reserve(i);
    vector<int> veci;
    veci.reserve(i);

    for (int n = 0; n < 50; ++n) {
      vecc.push_back(n);
      veci.push_back(static_cast<char>(n + 50));
    }
    veci.insert(veci.end(), vals.begin(), vals.end());

    while (vecc.size()) {
      score += vecc.back();
      vecc.pop_back();
    }
    while (veci.size()) {
      score += veci.back();
      veci.pop_back();
    }
  }

  printf("%ld\n", score);
  
  return 0;
}
