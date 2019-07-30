#include <iostream>
#include <array>

int getChange(int money) {
  const std::array<int, 3> changes{10, 5, 1};
  int minimum = 0;

  for ( const int change : changes ) {
    while ( money >= change ) {
      money -= change;
      minimum++;
    }
  }

  return minimum;
}

int main(void) {
  int m;
  std::cin >> m;
  std::cout << getChange(m) << '\n';

  return 0;
}