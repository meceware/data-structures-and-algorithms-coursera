#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <string.h>

using std::make_pair;
using std::pair;
using std::string;
using std::vector;
using std::map;

const map<char, int> Alphabet{ {'$', 0}, {'A', 1}, {'C', 2}, {'G', 3}, {'T', 4} };
const unsigned int AlpabetSize = Alphabet.size();

void sortChars(const string& text, vector<int>& order) {
  const int textSize = text.size();
  vector<int> count(AlpabetSize, 0);

  order.resize(textSize);
  for (const char c : text) {
    const int index = Alphabet.at(c);
    count[index]++;
  }

  for (unsigned int i = 1; i < AlpabetSize; ++i) {
    count[i] += count[i - 1];
  }

  for (unsigned int i = textSize; i > 0; --i) {
    const int index = Alphabet.at(text[i - 1]);
    count[index]--;
    order[count[index]] = i - 1;
  }
}

void computeCharClasses(const string& text, const vector<int>& order, vector<int>& cls) {
  const int textSize = text.size();

  cls.resize(textSize);
  cls[order[0]] = 0;
  for (unsigned int i = 1; i < textSize; ++i) {
    cls[order[i]] = text[order[i]] != text[order[i - 1]] ?  cls[order[i - 1]] + 1 : cls[order[i - 1]];
  }
}

vector<int> sortDoubled(const string& text, const int length, const vector<int>& order, const vector<int>& cls) {
  const int textSize = text.size();
  vector<int> newOrder(textSize, 0);
  vector<int> count(textSize, 0);

  for (unsigned int i = 0; i < textSize; ++i) {
    count[cls[i]]++;
  }

  for (unsigned int i = 1; i < textSize; ++i) {
    count[i] += count[i - 1];
  }

  for (unsigned int i = textSize; i > 0; --i) {
    int start = (order[i - 1] - length + textSize) % textSize;
    int cl = cls[start];
    count[cl]--;
    newOrder[count[cl]] = start;
  }

  return newOrder;
}

vector<int> updateClasses(const vector<int>& order, const vector<int>& cls, const int length) {
  const int textSize = order.size();

  vector<int> newCls(textSize, 0);

  for (unsigned int i = 1; i < textSize; ++i) {
    int current = order[i];
    int prev = order[i - 1];
    int mid = (current + length) % textSize;
    int midPrev = (prev + length) % textSize;

    newCls[current] = (cls[current] != cls[prev] || cls[mid] != cls[midPrev]) ? newCls[prev] + 1 : newCls[prev];
  }

  return newCls;
}

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> buildSuffixArray(const string& text) {
  const unsigned int textSize = text.size();

  vector<int> order;
  sortChars(text, order);

  vector<int> cls;
  computeCharClasses(text, order, cls);

  unsigned int length = 1;
  while (length < textSize) {
    order = sortDoubled(text, length, order, cls);
    cls = updateClasses(order, cls, length);

    length <<= 1;
  }

  return std::move(order);
}

void findOccurrences(const string& pattern, const string& text, const vector<int>& suffixArray, vector<bool> &occurs) {
  const unsigned int textSize = text.size();
  const unsigned int patternSize = pattern.size();

  unsigned int minIndex = 0;
  unsigned int maxIndex = textSize;

  while (minIndex < maxIndex) {
    unsigned int mid = (minIndex + maxIndex) >> 1;
    if (pattern.compare(0, patternSize, text, suffixArray[mid], patternSize) > 0) {
      minIndex = mid + 1;
    } else {
      maxIndex = mid;
    }
  }

  unsigned int start = minIndex;

  maxIndex = textSize;
  while (minIndex < maxIndex) {
    unsigned int mid = (minIndex + maxIndex) >> 1;
    if (pattern.compare(0, patternSize, text, suffixArray[mid], patternSize) < 0) {
      maxIndex = mid;
    } else {
      minIndex = mid + 1;
    }
  }

  unsigned int end = maxIndex;

  while (start < end) {
    occurs[suffixArray[start]] = true;
    start++;
  }
}

int main() {
  string text;
  std::cin >> text;
  text += '$';

  vector<int> suffixArray = buildSuffixArray(text);

  int patternCount;
  std::cin >> patternCount;

  vector<bool> occurs(text.length(), false);
  string pattern;
  for (int i = 0; i < patternCount; ++i) {
    std::cin >> pattern;
    findOccurrences(pattern, text, suffixArray, occurs);
  }

  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      std::cout << i << " ";
    }
  }

  std::cout << std::endl;
  return 0;
}
