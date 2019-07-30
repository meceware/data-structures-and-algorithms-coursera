#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>

using std::vector;
using std::swap;
using std::pair;

pair<int, int> partition3( vector<int> &a, int left, int right ) {
  int pivot = a[left];
  int mid = left;

  while ( mid <= right ) {
    if ( a[mid] == pivot ) {
      mid++;
    } else if ( a[mid] < pivot ) {
      swap( a[left], a[mid] );
      left++;
      mid++;
    } else {
      swap( a[mid], a[right] );
      right -= 1;
    }
  }

  return std::make_pair( left, right );
}

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  pair<int, int> m = partition3(a, l, r);

  randomized_quick_sort(a, l, m.first - 1);
  randomized_quick_sort(a, m.second + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
