#include <iostream>
#include <vector>
#include <limits>

using std::vector;

int get_change(int money) {
  const vector<int> coins{1, 3, 4};

  vector<int> minNumCoins( money + 1 );
  minNumCoins[ 0 ] = 0;
  for ( int m = 1; m <= money; m++ ) {
    minNumCoins[ m ] = std::numeric_limits<int>::max() ;
    for ( const auto coin : coins ) {
      if ( m >= coin ) {
        const int num = minNumCoins[ m - coin ] + 1;
        if ( num < minNumCoins[ m ] ) {
          minNumCoins[ m ] = num;
        }
      }
    }
  }

  //write your code here
  return minNumCoins[ money ];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
