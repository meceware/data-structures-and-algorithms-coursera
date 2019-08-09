#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();

    // const auto getParent = []( int i ) {
    //   return ( i - 1 ) / 2;
    // };

    const auto getLeftChild = []( int i ) {
      return 2 * i + 1;
    };

    const auto getRightChild = []( int i ) {
      return 2 * (i + 1);
    };

    const int size = data_.size();

    const auto getMinOfChild = [ this, size, &getLeftChild, &getRightChild ]( int i ) {
      int leftChild = getLeftChild( i );
      int rightChild = getRightChild( i );

      i = ( leftChild < size ) && ( data_[ leftChild ] < data_[ i ] ) ? leftChild : i;
      i = ( rightChild < size ) && ( data_[ rightChild ] < data_[ i ] ) ? rightChild : i;

      return i;
    };

    const auto siftDown = [ this, &getMinOfChild ]( int i ) {
      int minIndex;
      while ( i != ( minIndex = getMinOfChild( i ) ) ) {
        swaps_.push_back( std::make_pair( i, minIndex ) );
        std::swap( data_[ i ], data_[ minIndex ] );

        i = minIndex;
      }
    };

    for ( int i = size / 2; i >= 0; --i ) {
      siftDown( i );
    }

#ifdef _NAIVE_
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i) {
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
    }
#endif
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();

    // Check the output
    if ( swaps_.size() > 4 * data_.size() ) {
      cout << "Something wrong!!!" << std::endl;
    }

    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
