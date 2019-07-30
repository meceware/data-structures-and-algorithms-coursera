#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

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

int main() {
  int distance = 0;
  cin >> distance;
  int miles = 0;
  cin >> miles;
  int n = 0;
  cin >> n;

  vector<int> stops(n + 2);
  stops[0] = 0; // Initial value
  for (size_t i = 1; i <= n; ++i) {
    cin >> stops.at( i );
  }
  stops[n + 1] = distance;

  cout << compute_min_refills( miles, stops) << "\n";

  return 0;
}
