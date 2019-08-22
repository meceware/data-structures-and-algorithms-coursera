#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

struct Index {
  int start;
  int count;

  Index() : start(0), count(0) {}
};

string InverseBWT(const string& bwt) {
  const auto bwtSize{bwt.size()};
  if (!bwtSize) {
    return "";
  }

  // Generate counts
  map<char, Index> counters;
  vector<int> rank(bwtSize);
  for (auto i{0}; i < bwtSize; ++i) {
    const auto c = bwt[i];
    rank[i] = counters[c].count;
    counters[c].count++;
  }

  // Generate indexes
  auto it{counters.begin()};
  auto prev{it};
  it++;
  while (it != counters.end()) {
    it->second.start = prev->second.start + prev->second.count;
    prev = it;
    it++;
  }

  // Put the strings in reverse order
  string text;
  text.resize(bwtSize);
  text[bwtSize - 1] = '$';
  int lastCol{0};
  for (auto i{bwtSize - 1}; i > 0; --i) {
    auto c{bwt[lastCol]};
    text[i - 1] = c;
    Index& index = counters[c];
    lastCol = index.start + rank[lastCol];
  }

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
