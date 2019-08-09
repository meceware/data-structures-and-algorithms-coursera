#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;

void maxSlidingWindow( vector<int> const & numbers, int w ) {
  std::deque<int> deq;

  // Find maximum element of the first sliding window
  for ( int i = 0; i < w; i++ ) {
    while ( ! deq.empty() && numbers[ i ] >= numbers[ deq.back() ] ) {
      deq.pop_back();
    }
    deq.push_back( i );
  }

  int size = numbers.size();
  for ( int i = w; i < size; i++ ) {
    cout << numbers[ deq.front() ] << " ";

    while ( ! deq.empty() && deq.front() <= (i - w) ) {
      deq.pop_front();
    }

    while ( ! deq.empty() && numbers[ i ] >= numbers[ deq.back() ] ) {
      deq.pop_back();
    }

    deq.push_back( i );
  }

  cout << numbers[ deq.front() ] << " ";
}

void max_sliding_window_naive(vector<int> const & A, int w) {
  for (size_t i = 0; i < A.size() - w + 1; ++i) {
    int window_max = A.at(i);
    for (size_t j = i + 1; j < i + w; ++j) {
      window_max = max(window_max, A.at(j));
    }

    cout << window_max << " ";
  }

  return;
}


int main() {
  int n = 0;
  cin >> n;

  vector<int> A(n);
  for (size_t i = 0; i < n; ++i)
      cin >> A.at(i);

  int w = 0;
  cin >> w;

  // max_sliding_window_naive(A, w); // TODO
  // std::cout << std::endl; // TODO
  maxSlidingWindow(A, w);

  return 0;
}
