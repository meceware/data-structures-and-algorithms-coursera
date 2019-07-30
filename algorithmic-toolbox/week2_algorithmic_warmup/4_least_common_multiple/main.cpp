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

long long lcm( int a, int b ) {
  int common = gcd( a, b );

  return (long long)(a / common) * (long long)b;
}

#ifdef _TEST_
int naive( int a, int b ) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

void test() {
  for (int a = 1; a <= 1000; ++a) {
    for (int b = 1; b <= 1000; ++b) {
      int r = naive( a, b );
      int f = lcm( a, b );
      if ( r != f ) {
        std::cout << "Fail! LCM for " << a << " and " << b << " is " << r << " but calculated " << f << std::endl;
        system("pause");
        return;
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

  std::cout << lcm( a, b ) << '\n';

  return 0;
}