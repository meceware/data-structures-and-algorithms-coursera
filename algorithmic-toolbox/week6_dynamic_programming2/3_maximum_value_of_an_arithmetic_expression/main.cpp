#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using std::vector;
using std::string;
using std::max;
using std::min;
using std::pair;

typedef pair< long long, long long > LongPair;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }

  return 0;
}

long long get_maximum_value(const string &exp) {
  // Since every digit is a single charachter, it goes d op d op d = 2n + 1
  int length = exp.size();
  int numbersLength = ( length + 1 ) / 2;
  // Pair.first is min, pair.second is max
  vector< vector< LongPair > > minMax( numbersLength, vector< LongPair >( numbersLength ) );

  for ( unsigned int i = 0 ; i < numbersLength; i++ ) {
    long long number = std::stoll( exp.substr( 2 * i, 1) );
    minMax[ i ][ i ].first = number;
    minMax[ i ][ i ].second = number;
  }

  for ( unsigned int s = 0; s < numbersLength - 1; s++ ) {
    for ( unsigned int i = 0 ; i < numbersLength - s - 1; i++ ) {
      unsigned int j = s + i + 1;
      long long minAll = std::numeric_limits<long long>::max();
      long long maxAll = std::numeric_limits<long long>::min();
      for ( unsigned int k = i ; k < j; k++ ) {
        char op = exp[ 2 * k + 1 ];
        long long a = eval( minMax[ i ][ k ].second, minMax[ k + 1 ][ j ].second, op );
        long long b = eval( minMax[ i ][ k ].second, minMax[ k + 1 ][ j ].first, op );
        long long c = eval( minMax[ i ][ k ].first, minMax[ k + 1 ][ j ].second, op );
        long long d = eval( minMax[ i ][ k ].first, minMax[ k + 1 ][ j ].first, op );

        minAll = min( { minAll, a, b, c, d } );
        maxAll = max( { maxAll, a, b, c, d } );
      }

      minMax[ i ][ j ].first = minAll;
      minMax[ i ][ j ].second = maxAll;
    }
  }

  return minMax[ 0 ][ numbersLength - 1 ].second;
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
