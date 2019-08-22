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

string BWT(const string& text) {
  const int textSize = text.size();

  map<string, int> suffixArray;
  for (unsigned int i = 0; i < textSize; ++i) {
    suffixArray[ text.substr(i, textSize) ] = i;
  }

  string result;
  result.reserve(textSize);
  for (const auto& suffix : suffixArray) {
    result.push_back(suffix.second ? text[suffix.second - 1] : '$');
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}