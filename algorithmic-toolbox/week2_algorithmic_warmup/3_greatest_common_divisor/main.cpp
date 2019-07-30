#include <iostream>

// TODO: remove
// #define _TEST_

int gcd( int a, int b ) {
  while ( b != 0 ) {
    int rem = a % b;
    a = b;
    b = rem;
  }

  return a;
}

#ifdef _TEST_
int naive( int a, int b ) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

void test() {
  for (int a = 1; a <= 1000000; ++a) {
    for (int b = 1; b <= 1000000; ++b) {
      int r = naive( a, b );
      int f = gcd( a, b );
      if ( r != f ) {
        std::cout << "Fail! GCD for " << a << " and " << b << " is " << r << " but calculated " << f << std::endl;
        break;
      } else {
        std::cout << "OK! " << a << " and " << b << " is " << f << std::endl;
      }
    }
  }

  std::cout << "Test Completed!" << std::endl;
}
#endif

int main(void) {
#ifdef _TEST_
  test();
#endif

  int a, b;
  std::cin >> a >> b;

  std::cout << gcd( a, b ) << '\n';

  return 0;
}