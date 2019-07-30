#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

// #define _TEST_

string largest_number(vector<string> &numbers) {
  std::sort( numbers.begin(), numbers.end(), []( string a, string b ) {
    if ( a[0] > b[0] )
      return true;

    if ( a[0] < b[0] )
      return false;

    std::stringstream ret;
    int x, y;
    ret << a << b;
    ret >> x;
    ret.clear();
    ret << b << a;
    ret >> y;

    return x > y;
  } );

  std::stringstream ret;
  for ( const auto& number : numbers ) {
    ret << number;
  }

  return ret.str();
}

int main() {
#ifdef _TEST_
  {
    vector<string> numbers {"21", "2"};
    std::cout << largest_number( numbers ) << std::endl;
    numbers = {"21", "3"};
    std::cout << largest_number( numbers ) << std::endl;
    numbers = {"21", "1"};
    std::cout << largest_number( numbers ) << std::endl;
    numbers = {"23", "2"};
    std::cout << largest_number( numbers ) << std::endl;
  }
#endif

  int n;
  std::cin >> n;
  vector<string> numbers(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> numbers[i];
  }
  std::cout << largest_number( numbers );
}
