#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::min;

vector<int> optimal_sequence( int n ) {
  vector<int> result( n + 1 );
  result[0] = 0;
  result[1] = 0;
  for ( int i = 2; i <= n; i++ ) {
    int minResult = result[ i - 1 ];

    if ( i % 2 == 0 ) {
      minResult = min( minResult, result[ i / 2 ] );
    }

    if ( i % 3 == 0 ) {
      minResult = min( minResult, result[ i / 3 ] );
    }

    result[ i ] = minResult + 1;
  }

  std::vector<int> sequence;

  while ( n ) {
    sequence.push_back( n );
    int minResult = result[ n ] - 1;
    if ( n % 3 == 0 && minResult == result[ n / 3 ] ) {
      n /= 3;
    } else if ( n % 2 == 0 && minResult == result[ n / 2 ] ) {
      n /= 2;
    } else /* if ( minResult == result[ n - 1 ] ) */ {
      n--;
    }
  }

  reverse(sequence.begin(), sequence.end());
  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
