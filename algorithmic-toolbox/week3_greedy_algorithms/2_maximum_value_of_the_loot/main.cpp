#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using std::vector;

struct WeightValuePair {
  int weight;
  int value;
  double valuePerWeight;
};

double get_optimal_value(int capacity, vector< WeightValuePair >& weightsAndValues) {
  double sum = 0.0;

  std::sort( weightsAndValues.begin(), weightsAndValues.end(), []( const WeightValuePair &a, const WeightValuePair &b ) {
    return ( a.valuePerWeight > b.valuePerWeight );
  } );

  for ( const auto& val : weightsAndValues ) {
    // std::cout << "sorted weight " << val.weight << " and value " << val.value << " which has " << val.valuePerWeight << std::endl;

    if ( capacity < val.weight ) {
      sum += val.valuePerWeight * capacity;
      capacity = 0;
      break;
    }

    capacity -= val.weight;
    sum += val.value;

    if ( !capacity ) {
      break;
    }
  }

  return sum;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector< WeightValuePair > weightsAndValues(n);
  for (int i = 0; i < n; i++) {
    int value, weight;
    std::cin >> value >> weight;
    weightsAndValues[i] = { weight, value, (double)value / (double)weight };
  }

  double optimal_value = get_optimal_value(capacity, weightsAndValues);

  std::cout << std::fixed << std::setprecision(4) << optimal_value << std::endl;
  return 0;
}
