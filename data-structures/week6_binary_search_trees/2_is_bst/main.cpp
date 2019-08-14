#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// #define _DEBUG

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key, int left, int right) : key(key), left(left), right(right) {}
};

bool IsBinarySearchTree( const vector<Node>& tree ) {
  std::stack<int> s;
  int index = 0;
  int min = std::numeric_limits<int>::min();

  while ( !s.empty() || index != -1 )
  {
    // if ( index != -1 ) cout << "going with " << tree[ index ].key << endl;
    // Go through left
    while ( index != -1 )
    {
      #ifdef _DEBUG
      cout << "Pushing node: " << tree[ index ].key << endl;
      #endif

      s.push( index );
      index = tree[ index ].left;
    }

    // Now go right
    index = s.top();
    s.pop();

    #ifdef _DEBUG
    cout << "popping node " << tree[ index ].key << " min: " << min << endl;
    #endif

    if ( tree[ index ].key <= min ) {
      return false;
    }

    min = tree[ index ].key;
    index = tree[ index ].right;
  }

  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back( { key, left, right } );
  }

  if ( nodes == 0 || IsBinarySearchTree( tree ) ) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }

  return 0;
}
