#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int compute_min_refills(int tankMiles, vector<int> & stops) {
  const int undefined = -1;
  int size = stops.size() - 1;

  // If distance is less than the tank, return no stop necessary, 0
  if ( stops[size] <= tankMiles ) {
    return 0;
  }

  int gone = stops[0]; // Start at the initial
  unsigned int min = 0; // minimum number of stops
  unsigned int i = 0;

  while ( i < size ) {
    while ( i < size && ( stops[ i + 1 ] - gone ) <= tankMiles ) {
      i++;
    }

    // If with the tank it can't be gone, then return 0
    if ( gone == stops[i] ) {
      return undefined;
    }

    gone = stops[i];
    min++;
  }

  return min - 1;
}



long long max_dot_product(vector<int> profitPerClick, vector<int> avgNumberOfClicks) {
  std::sort (profitPerClick.begin(), profitPerClick.end(), std::greater<int>());
  std::sort (avgNumberOfClicks.begin(), avgNumberOfClicks.end(), std::greater<int>());

  unsigned int size = profitPerClick.size();
  long long result = 0;

  for ( unsigned int i = 0; i < size; i++ ) {
    result += (long long)profitPerClick[i] * (long long)avgNumberOfClicks[i];
  }

  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> profitPerClick(n), avgNumberOfClicks(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> profitPerClick[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> avgNumberOfClicks[i];
  }
  std::cout << max_dot_product(profitPerClick, avgNumberOfClicks) << std::endl;
}
