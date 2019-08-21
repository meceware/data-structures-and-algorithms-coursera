#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> Edges;
typedef vector<Edges> Trie;

Trie build_trie(vector<string> & patterns) {
  if (patterns.empty()) {
    return {};
  }

  Trie t;
  t.emplace_back( Edges{} );

  int counter{0};
  for (const auto& pattern : patterns) {
    int current{0};

    for (const auto c : pattern) {
      Edges& tCurrent = t[current];

      if (tCurrent.find(c) != tCurrent.end()) {
        current = tCurrent[c];
      } else {
        t.emplace_back( Edges{} );
        counter++;
        t[current][c] = counter;
        current = counter;
      }
    }
  }

  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  Trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}