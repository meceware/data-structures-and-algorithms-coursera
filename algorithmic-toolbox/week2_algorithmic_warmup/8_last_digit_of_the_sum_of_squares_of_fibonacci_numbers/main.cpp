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

unsigned int fibonacci_sum_squares( unsigned long long n ) {
  if (n <= 1) {
    return n;
  }

  std::vector<unsigned int> numbers;

  getSequence( numbers, n, 10 );

  int size = numbers.size();
  unsigned int sum = numbers[ n % size ];
  sum = ( sum + numbers[ ( n-1 ) % size ] ) * sum;

  return sum % 10;
}

#ifdef _TEST_
unsigned long long naive(unsigned long long n) {
  if (n <= 1)
    return n;

  unsigned long long previous = 0;
  unsigned long long current  = 1;
  unsigned long long sum      = 1;

  for (long long i = 0; i < n - 1; ++i) {
    unsigned long long tmp_previous = previous;
    previous = current;
    current = tmp_previous + current;
    sum += current * current;
  }

  return sum % 10;
}

void test() {
  for (unsigned long long n = 0; n <= 64; ++n) {
    unsigned int r = naive( n );
    unsigned int f = fibonacci_sum_squares( n );
    if ( r != f ) {
      std::cout << "Fail! Fibonacci for " << n << " is " << r << " but calculated " << f << std::endl;
      system("pause");
      return;
    } else {
      std::cout << "OK! " << n << " is " << f << std::endl;
    }
  }
}
#endif

int main(void) {
#ifdef _TEST_
  test();
#endif

  long long n = 0;
  std::cin >> n;
  std::cout << fibonacci_sum_squares( n ) << '\n';

  return 0;
}