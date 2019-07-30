#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;

int lcs2( vector<int> &a, vector<int> &b ) {
  int aSize = a.size();
  int bSize = b.size();

  int d[ aSize + 1 ][ bSize + 1 ];

  for ( int i = 0; i <= aSize; i++ ) {
    d[ i ][ 0 ] = 0;
  }

  for ( int i = 0; i <= bSize; i++ ) {
    d[ 0 ][ i ] = 0;
  }

  for ( int i = 1; i <= aSize; i++ ) {
    for ( int j = 1; j <= bSize; j++ ) {
      if ( a[ i - 1 ] == b[ j - 1 ] ) {
        d[ i ][ j ] = d[ i - 1 ][ j - 1 ] + 1;
      } else {
        d[ i ][ j ] = max( d[ i - 1 ][ j ], d[ i ][ j - 1 ] );
      }
    }
  }

  return d[ aSize ][ bSize ];
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
