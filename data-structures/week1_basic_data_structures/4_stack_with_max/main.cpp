#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <limits>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

struct StackWithMaxHolder {
  int value;
  int max;
};

class StackWithMax {
  private:
    vector< StackWithMaxHolder > stack;
    int maxValue;

    int getMin() const {
      return std::numeric_limits<int>::min();
    }

  public:

    StackWithMax() : stack(), maxValue( getMin() ) {}

    void Push(int value) {
      if ( value > maxValue ) {
        maxValue = value;
      }
      stack.push_back( { value, maxValue } );
    }

    void Pop() {
      if ( stack.empty() ) {
        return;
      }

      stack.pop_back();
      maxValue = stack.empty() ? getMin() : stack.back().max;
    }

    int Max() const {
      assert(stack.size());

      return maxValue;
    }
};

int main() {
  int num_queries = 0;
  cin >> num_queries;

  string query;
  string value;

  StackWithMax stack;

  for (int i = 0; i < num_queries; ++i) {
    cin >> query;
    if (query == "push") {
      cin >> value;
      stack.Push(std::stoi(value));
    }
    else if (query == "pop") {
      stack.Pop();
    }
    else if (query == "max") {
      cout << stack.Max() << "\n";
    }
    else {
      assert(0);
    }
  }
  return 0;
}