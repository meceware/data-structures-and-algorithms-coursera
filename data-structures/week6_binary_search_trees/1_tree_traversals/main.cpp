#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

struct TreeInfo {
  int key;
  int left;
  int right;
};

class TreeOrders {
  int n;
  vector<TreeInfo> treeInfo;

public:
  void read() {
    cin >> n;

    treeInfo.resize(n);

    for (int i = 0; i < n; i++) {
      cin >> treeInfo[ i ].key >> treeInfo[ i ].left >> treeInfo[ i ].right;
    }
  }

  void inOrderRecursive( vector<int>& result, int index ) {
    // If index is -1, it's root
    if ( index == -1 ) {
      return;
    }

    inOrderRecursive( result, treeInfo[ index ].left );
    result.push_back( treeInfo[ index ].key );
    inOrderRecursive( result, treeInfo[ index ].right );
  }

  vector <int> in_order() {
    vector<int> result;
    inOrderRecursive( result, 0 ) ;

    return result;
  }

  void preOrderRecursive( vector<int>& result, int index ) {
    // If index is -1, it's root
    if ( index == -1 ) {
      return;
    }

    result.push_back( treeInfo[ index ].key );
    preOrderRecursive( result, treeInfo[ index ].left );
    preOrderRecursive( result, treeInfo[ index ].right );
  }

  vector <int> pre_order() {
    vector<int> result;    
    preOrderRecursive( result, 0 );

    return result;
  }

  void postOrderRecursive( vector<int>& result, int index ) {
    // If index is -1, it's root
    if ( index == -1 ) {
      return;
    }

    postOrderRecursive( result, treeInfo[ index ].left );
    postOrderRecursive( result, treeInfo[ index ].right );
    result.push_back( treeInfo[ index ].key );
  }

  vector <int> post_order() {
    vector<int> result;
    postOrderRecursive( result, 0 );
    
    return result;
  }
};

void print(vector<int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}
