#include <iostream>
#include <vector>

// TODO: remove
// #define _TEST_

unsigned int fibonacciLastDigit( unsigned long long n, unsigned int m ) {
  if ( n <= 1 ) {
    return n;
  }

  unsigned int prev = 0;
  unsigned int total = 1;

  for (unsigned long long i = 2; i <= n; ++i) {
    unsigned int sum = total;
    total = ( total + prev ) % m;
    prev = sum;
  }

  return total;
}

void getSequence( std::vector<unsigned int>& numbers, unsigned long long n, unsigned int m ) {
  numbers.push_back( fibonacciLastDigit( 0, m ) );

  for ( unsigned long long i = 1; i <= n; ++i ) {
    unsigned int fib = fibonacciLastDigit( i, m );

    if ( fib == 0 ) {
      unsigned int fib2 = fibonacciLastDigit( i + 1, m );
      if ( fib2 == 1 ) {
        return;
      }

      numbers.push_back( fib );
      numbers.push_back( fib2 );
      i++;
    } else {
      numbers.push_back( fib );
    }
  }
}

unsigned int get_fibonacci_huge_naive(unsigned long long n, unsigned int m) {
  std::vector<unsigned int> numbers;

  getSequence( numbers, n, m );

  return numbers[ n % numbers.size() ];
}

#ifdef _TEST_
unsigned long long naive(unsigned long long n, unsigned int m) {
    if (n <= 1)
        return n;

    unsigned long long previous = 0;
    unsigned long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

void test() {
  for (unsigned int m = 2; m <= 4; ++m) {
    for (unsigned long long n = 1; n <= 64; ++n) {
      unsigned long long r = naive( n, m );
      unsigned long long f = get_fibonacci_huge_naive( n, m );
      if ( r != f ) {
        std::cout << "Fail! Fibonacci for " << n << " and " << m << " is " << r << " but calculated " << f << std::endl;
        system("pause");
        return;
      } else {
        std::cout << "OK! " << n << " and " << m << " is " << f << std::endl;
      }
    }
  }
}
#endif

int main(void) {
#ifdef _TEST_
  test();
#endif

  unsigned long long n;
  unsigned int m;
  std::cin >> n >> m;
  std::cout << get_fibonacci_huge_naive( n, m ) << '\n';

  return 0;
}