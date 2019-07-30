#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using std::vector;
using std::max;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  int aSize = a.size();
  int bSize = b.size();
  int cSize = c.size();

  int d[ aSize + 1 ][ bSize + 1 ][ cSize + 1 ]{};

  for ( int i = 1; i <= aSize; i++ ) {
    for ( int j = 1; j <= bSize; j++ ) {
      for ( int k = 1; k <= cSize; k++ ) {
        if ( a[ i - 1 ] == b[ j - 1 ] && a[ i - 1 ] == c[ k - 1 ] ) {
          d[ i ][ j ][ k ] = d[ i - 1 ][ j - 1 ][ k - 1 ] + 1;
        } else {
          d[ i ][ j ][ k ] = max( { d[ i - 1 ][ j ][ k ], d[ i ][ j - 1 ][ k ], d[ i ][ j ][ k - 1 ] } );
        }
      }
    }
  }

  return d[ aSize ][ bSize ][ cSize ];
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}

