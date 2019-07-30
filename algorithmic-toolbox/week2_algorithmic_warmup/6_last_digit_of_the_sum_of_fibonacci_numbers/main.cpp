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

#ifdef _TEST_
int naive(unsigned long long n) {
	if (n <= 1)
		return (int)n;

	long long previous = 0;
	long long current = 1;
	long long sum = 1;

	for (unsigned long long i = 0; i < n - 1; ++i) {
		long long tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
		sum += current;
	}

	return sum % 10;
}

void test() {
	for (unsigned long long n = 1; n <= 64; ++n) {
		unsigned long long r = naive(n);
		unsigned long long f = fibonacci_sum(n);
		if (r != f) {
			std::cout << "Fail! Fibonacci for " << n << " is " << r << " but calculated " << f << std::endl;
			system("pause");
			return;
		}
		else {
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
	std::cout << fibonacci_sum(n) << "\n";

	return 0;
}