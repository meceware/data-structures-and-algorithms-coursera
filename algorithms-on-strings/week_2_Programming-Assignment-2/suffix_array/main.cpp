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

vector<int> BuildSuffixArray(const string& text) {
  const int textSize = text.size();

  map<string, int> suffixArray;
  for (unsigned int i = 0; i < textSize; ++i) {
    suffixArray[ text.substr(i, textSize) ] = i;
  }

  vector<int> result;
  std::transform(suffixArray.begin(), suffixArray.end(), std::back_inserter(result),
    [](const std::pair<string, int> &item) {
      return item.second;
    }
  );

  return result;
}

int main() {
  string text;
  cin >> text;

  vector<int> suffixArray = BuildSuffixArray(text);
  for (const auto suffix : suffixArray) {
    cout << suffix << ' ';
  }
  cout << endl;

  return 0;
}