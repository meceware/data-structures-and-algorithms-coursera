#include <iostream>
#include <vector>

using std::vector;

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  if (right <= left + 1) {
    return 0;
  }

  size_t ave = (right + left) / 2;
  long long number_of_inversions = 0;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);

  size_t iLeft = left;
  size_t iAve = ave;
  size_t iReal = left;

  while ( iLeft < ave && iAve < right ) {
    if ( a[ iLeft ] > a[ iAve ] ) {
      b[ iReal ] = a[ iAve++ ];
      number_of_inversions += ave - iLeft;
    } else {
      b[ iReal ] = a[ iLeft++ ];
    }

    iReal++;
  }

  while ( iLeft < ave ) {
    b[ iReal++ ] = a[ iLeft++ ];
  }

  while ( iAve < right ) {
    b[ iReal++ ] = a[ iAve++ ];
  }

  for ( iLeft = left; iLeft < right; iLeft++ ) {
    a[ iLeft ] = b[ iLeft ];
  }

  return number_of_inversions;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());

  std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';

#if 0
  std::cout << "Sorted Array: "; // TODO: remove
  for (const int i : b) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
#endif
}
