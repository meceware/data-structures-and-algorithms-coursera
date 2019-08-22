#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position
//       of this character in the sorted array of
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, vector<map<char, int>>& starts, map<char, int>& occ) {
  const int bwtSize = bwt.size();

  string sorted = bwt;
  sort(sorted.begin(), sorted.end());

  for (auto i{0}; i < bwtSize; ++i) {
    auto c = sorted[i];
    if (occ.find(c) == occ.end()) {
      occ[c] = i;
    }
  }

  starts.resize(bwtSize + 1);
  for (auto i{0}; i < bwtSize; ++i) {
    for (const auto& o : occ) {
      starts[i + 1][o.first] = starts[i][o.first];
    }
    starts[i + 1][bwt[i]]++;
  }
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, const string& bwt, vector<map<char, int>>& starts, map<char, int>& occ) {
  const int bwtSize = bwt.size();
  const int patternSize = pattern.size();

  int top{0};
  int bottom{bwtSize - 1};
  int patternCount{patternSize - 1};
  while (top <= bottom) {
    if (patternCount >= 0) {
      const auto patternC{pattern[patternCount]};
      patternCount--;

      if (starts[bottom + 1][patternC] - starts[top][patternC]) {
        top = occ[patternC] + starts[top][patternC];
        bottom = occ[patternC] + starts[bottom + 1][patternC] - 1;
      } else {
        return 0;
      }
    } else {
      break;
    }
  }

  return bottom - top + 1;
}


int main() {
  string bwt;
  std::cin >> bwt;

  int pattern_count;
  std::cin >> pattern_count;

  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  vector<map<char, int>> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);

  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    std::cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    std::cout << occ_count << " ";
  }

  std::cout << std::endl;

  return 0;
}
