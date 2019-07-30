#include <iostream>
#include <vector>

using std::vector;

// #define

void optimal_summands(int n, vector<int> &summands) {
  int start = 1;
  int sum = 0;
  while ( sum < n ) {
    int number = n - sum - start;
    if ( number > 0 && number <= start ) {
      start++;
      continue;
    }
    sum += start;
    summands.push_back( start );
    start++;
  }
}

int main() {
#ifdef _TEST_
  {
    vector<int> summands;
    for (int i = 1; i <= 50; i++) {
      optimal_summands(i, summands);
      summands.clear();
    }
  }
#endif

  int n;
  std::cin >> n;
  vector<int> summands;
  optimal_summands(n, summands);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
