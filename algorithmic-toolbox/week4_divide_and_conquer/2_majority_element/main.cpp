#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_majority_element(vector<int> &a, unsigned int left, unsigned int right) {
  if ( left == right ) {
    return -1;
  }

  if ( left + 1 == right ) {
    return a[left];
  }

  unsigned int majority = ( right - left) / 2;
  unsigned int mid = left + majority;
  int leftMajor = get_majority_element( a, left, mid );
  int rightMajor = get_majority_element( a, mid, right );

  if ( leftMajor == rightMajor ) {
    return leftMajor;
  }

  if ( leftMajor != -1 ) {
    unsigned int count = 0;
    for ( unsigned int i = left; i < right; i++ ) {
        if ( a[ i ] == leftMajor) {
          count++;
        }
    }

    if ( count > majority ) {
      return leftMajor;
    }
  }

  if ( rightMajor != -1 ) {
    unsigned int count = 0;
    for ( unsigned int i = left; i < right; i++ ) {
        if ( a[ i ] == rightMajor) {
          count++;
        }
    }

    if ( count > majority ) {
      return rightMajor;
    }
  }

  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
