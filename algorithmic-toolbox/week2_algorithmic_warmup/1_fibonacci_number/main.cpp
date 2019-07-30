#include <iostream>

// TODO: remove
// #define _TEST_

int fibonacci(int n) {
  if (n <= 1) {
    return n;
  }

  int prev = 0;
  int total = 1;

  for (int i = 2; i <= n; i++) {
    int sum = total;
    total += prev;
    prev = sum;
  }

  return total;
}

#ifdef _TEST_
unsigned long long fibonacciTest(unsigned int n) {
  if (n <= 1) {
    return n;
  }

  return fibonacciTest(n - 1) + fibonacciTest(n - 2);
}

void test() {
  for (int i = 0; i <= 45; ++i) {
    int r = fibonacciTest( i );
    int f = fibonacci( i );
    if ( r != f ) {
      std::cout << "Fail! Fibonacci for " << i << " is " << r << " but calculated " << f << std::endl;
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

  std::cout << fibonacci( n ) << '\n';

  return 0;
}