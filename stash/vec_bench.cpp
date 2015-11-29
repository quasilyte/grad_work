#include <cstdio>
#include <vector>

using namespace std;

int main(void) {
  long score = 0;

  for (int i = 1; i < 50000; ++i) {
    vector<char> vecc;
    vecc.reserve(i);
    vector<int> veci;
    veci.reserve(i);

    for (int n = 0; n < 50; ++n) {
      vecc.push_back(n);
      veci.push_back(static_cast<char>(n + 50));
    }

    while (vecc.size() && veci.size()) {
      score += vecc.back();
      score += veci.back();
      vecc.pop_back();
      veci.pop_back();
    }
  }

  printf("%ld\n", score);
  
  return 0;
}
