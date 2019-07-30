#include <iostream>
#include <vector>

// TODO: remove
// #define _TEST_

unsigned int fibonacciLastDigit(unsigned long long n, unsigned int m) {
	if (n <= 1) {
		return (unsigned int)n;
	}

	unsigned int prev = 0;
	unsigned int total = 1;

	for (unsigned long long i = 2; i <= n; ++i) {
		unsigned int sum = total;
		total = (total + prev) % m;
		prev = sum;
	}

	return total;
}

unsigned int getSequence(std::vector<unsigned int>& numbers, unsigned long long n, unsigned int m) {
	unsigned int sum = 0;
	numbers.push_back(fibonacciLastDigit(0, m));

	for (unsigned long long i = 1; i <= n; ++i) {
		unsigned int fib = fibonacciLastDigit(i, m);

		if (fib == 0) {
			unsigned int fib2 = fibonacciLastDigit(i + 1, m);
			if (fib2 == 1) {
				return sum;
			}

			numbers.push_back(fib);
			numbers.push_back(fib2);
			i++;
			sum = (sum + fib + fib2) % m;
		}
		else {
			numbers.push_back(fib);
			sum = (sum + fib) % m;
		}
	}

	return sum;
}

unsigned int fibonacci_sum(unsigned long long n) {
	std::vector<unsigned int> numbers;

	unsigned int totalSum = getSequence(numbers, n, 10);

	int size = numbers.size();
	unsigned int sum = ((n / size) * totalSum) % 10;

	unsigned long long remainder = n % size;

	for (unsigned long long i = 1; i <= remainder; ++i) {
		sum += numbers[i % size];
		sum %= 10;
	}

	return sum;
}

unsigned int get_fibonacci_partial_sum( unsigned long long from, unsigned long long to ) {
  std::vector<unsigned int> numbers;

  unsigned int totalSum = getSequence( numbers, to, 10 );
  int size = numbers.size();

  unsigned int toSum = ((to / size) * totalSum) % 10;
  unsigned long long remainder = to % size;

	for (unsigned long long i = 1; i <= remainder; ++i) {
		toSum += numbers[i % size];
		toSum %= 10;
	}

  remainder = from % size;
  unsigned int fromSum = ((from / size) * totalSum) % 10;
  for (unsigned long long i = 1; i < remainder; ++i) {
		fromSum += numbers[i % size];
		fromSum %= 10;
	}

  unsigned int sum = fromSum > toSum ? 10 + toSum - fromSum : toSum - fromSum;

  return sum;
}

#ifdef _TEST_
long long naive(long long from, long long to) {
  long long sum = 0;

  long long current = 0;
  long long next  = 1;

  for (long long i = 0; i <= to; ++i) {
    if (i >= from) {
      sum += current;
    }

    long long new_current = next;
    next = next + current;
    current = new_current;
  }

  return sum % 10;
}

void test() {
  for (unsigned long long from = 1; from <= 90; ++from) {
    for (unsigned long long to = from; to <= 90; ++to) {
      unsigned long long r = naive( from, to );
      unsigned long long f = get_fibonacci_partial_sum( from, to );
      if ( r != f ) {
        std::cout << "Fail! Fibonacci for " << from << " to " << to << " is " << r << " but calculated " << f << std::endl;
        return;
      } else {
        std::cout << "OK! " << from << " to " << to << " is " << f << std::endl;
      }
    }
  }
}
#endif

int main(void) {
#ifdef _TEST_
  test();
#endif

  long long from, to;
  std::cin >> from >> to;
  std::cout << get_fibonacci_partial_sum(from, to) << '\n';

  return 0;
}