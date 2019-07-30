#include <iostream>

// TODO: remove
// #define _TEST_

int fibonacciLastDigit(int n) {
  if (n <= 1) {
    return n;
  }

  int prev = 0;
  int total = 1;

  for (int i = 2; i <= n; i++) {
    int sum = total;
    total = (total + prev) % 10;
    prev = sum;
  }

  return total;
}

#ifdef _TEST_
unsigned long long naive(unsigned int n) {
  if (n <= 1)
    return n;

  long long previous = 0;
  long long current  = 1;

  for (int i = 0; i < n - 1; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = tmp_previous + current;
  }

  return current;
}

void test() {
  for (int i = 0; i <= 1000000; ++i) {
    unsigned long long fib = naive( i );
    int r = fib % 10;
    int f = fibonacciLastDigit( i );
    if ( r != f ) {
      std::cout << "Fail! Fibonacci for " << i << " is " << fib << " and result is " << r << " but calculated " << f << std::endl;
      break;
    } else {
      std::cout << "OK! " << i << " is " << f << std::endl;
    }
  }
}
#endif

int main(void) {
#ifdef _TEST_
  test();
#endif

  int n = 0;
  std::cin >> n;

  std::cout << fibonacciLastDigit( n ) << '\n';

  return 0;
}