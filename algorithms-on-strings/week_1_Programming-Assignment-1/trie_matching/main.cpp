#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node {
	int next [Letters];

	Node () {
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const {
	  return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

typedef vector<Node> Trie;

int letterToIndex (char letter) {
  const unsigned int count = 4;
  const char letters[count]{'A', 'C', 'G', 'T'};

  for (unsigned int i = 0; i < count; ++i) {
    if (letters[i] == letter) {
      return i;
    }
  }

  assert (false);
  return -1;
}

Trie build(const vector<string> & patterns) {
  if (patterns.empty()) {
    return {};
  }

  Trie t;
  t.emplace_back( Node{} );

  int counter{0};
  for (const auto& pattern : patterns) {
    int current{0};

    for (const auto c : pattern) {
      int index = letterToIndex(c);
      int next = t[current].next[index];
      if (next != NA) {
        current = next;
      } else {
        counter++;
        t[current].next[index] = counter;
        t.emplace_back( Node{} );
        current = counter;
      }
    }
  }

  return t;
}

bool match(const Trie& t, const string& text, int start) {
  int next = 0;
  bool matched = false;

  while (!t[next].isLeaf() && start < text.size()) {
    const Node& node = t[next];
    next = node.next[letterToIndex(text[start])];

    if (next == NA) {
      break;
    }

    if (t[next].isLeaf()) {
      matched = true;
    }

    start++;
  }

  return matched;
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;

  Trie t = build(patterns);

	for (int i = 0; i < text.size(); ++i) {
    if (match(t, text, i)) {
      result.push_back(i);
    }
  }

	return result;
}

int main (void) {
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++) {
		cin >> patterns[i];
	}

	vector <int> ans = solve(t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++) {
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
