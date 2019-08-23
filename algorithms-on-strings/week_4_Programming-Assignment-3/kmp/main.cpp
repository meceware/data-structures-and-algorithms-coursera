#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

void prefix(const string& pattern, vector<int>& s) {
  const int patternSize = pattern.size();
  int border = 0;

  s.resize(patternSize);
  s[0] = 0;

  for (unsigned int i = 1; i < patternSize; ++i) {
    while (border > 0 && pattern[i] != pattern[border]) {
      border = s[border - 1];
    }
    border = (pattern[i] == pattern[border]) ? border + 1 : 0;
    s[i] = border;
  }
}

vector<int> find_pattern(const string& pattern, const string& text) {
  const unsigned int patternSize = pattern.size();
  const string newText = pattern + '$' + text;
  const unsigned int textSize = newText.size();

  vector<int> s;
  prefix(newText, s);

  vector<int> result;
  for (unsigned int i = patternSize + 1; i < textSize; ++i) {
    if (s[i] == patternSize) {
      result.push_back(i - (patternSize * 2));
    }
  }

  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;

  vector<int> result = find_pattern(pattern, text);
  for (const auto r : result) {
    cout << r << " ";
  }

  cout << std::endl;
  return 0;
}
