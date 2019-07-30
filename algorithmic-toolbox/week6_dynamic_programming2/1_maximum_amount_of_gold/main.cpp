#include <iostream>
#include <vector>

using std::vector;

int optimal_weight( int totalWeight, const vector<int> &goldBars ) {
  const int goldBarsSize = goldBars.size();

  vector< vector<int> > value( goldBarsSize + 1, vector<int>( totalWeight + 1 ) );

  for ( int i = 1; i <= goldBarsSize; ++i ) {
    for ( int w = 1; w <= totalWeight; ++w ) {
      value[ i ][ w ] = value[ i - 1 ][ w ];
      int wi = goldBars[ i - 1 ];
      if ( wi <= w ) {
        int val = value[ i - 1 ][ w - wi ] + wi;
        if ( value[ i ][ w ] < val ) {
          value[ i ][ w ] = val;
        }
      }
    }
  }

  return value[ goldBarsSize ][ totalWeight ];
}

int main() {
  int n, totalWeight;
  std::cin >> totalWeight >> n;
  vector<int> gold( n );
  for ( int i = 0; i < n; i++ ) {
    std::cin >> gold[i];
  }
  std::cout << optimal_weight( totalWeight, gold ) << std::endl;
}
