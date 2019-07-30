#include <iostream>
#include <vector>
#include <numeric>

using std::vector;

int partition3(vector<int> &souvenirs) {
  const int size = souvenirs.size();
  if ( size < 3 ) {
    return 0;
  }

  // The total should be divided by 3
  const int sum = std::accumulate( souvenirs.begin(), souvenirs.end(), 0 );

  if ( sum % 3 ) {
    return 0;
  }

  const int each = sum / 3;
  vector< vector< int > > partition( each + 1, vector< int >( size + 1 ) );

  for (unsigned int i = 1; i <= each; i++) {
    for (unsigned int j = 1; j <= size; j++) {
      int souvenir = souvenirs[ j - 1 ];
      partition[ i ][ j ] = partition[ i ][ j - 1 ];
      if ( souvenir == i ) {
        partition[ i ][ j ]++;
      } else if ( i > souvenir && partition[ i - souvenir ][ j - 1 ] ) {
        partition[ i ][ j ]++;
      }
    }
  }

  // The sum should be at least 2 so it's the sum of at least 3 of the before
  return partition[ each ][ size ] >= 2 ? 1 : 0;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
