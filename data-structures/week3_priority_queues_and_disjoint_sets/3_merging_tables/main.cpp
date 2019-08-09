#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
  int size, parent, rank;

  DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) : size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
  int size;
  int max_table_size;
  vector < DisjointSetsElement > sets;

  DisjointSets( int size ) : size( size ), max_table_size( 0 ), sets( size ) {
    for ( int i = 0; i < size; i++ ) {
      sets[i].parent = i;
    }
  }

  int getParent( int table ) {
    // In order to compress path, we would need to use stack to actually set the children parents to the real parent.
    // So in order to defy using a stack, recursion is used for the stack purposes
    if ( table != sets[ table ].parent ) {
      sets[ table ].parent = getParent( sets[ table ].parent );
    }

    return sets[ table ].parent;
  }

  void merge( int destination, int source ) {
    int realDestination = getParent( destination );
    int realSource = getParent( source );

    if ( realDestination != realSource ) {
      DisjointSetsElement &realSourceElement = sets[ realSource ];
      DisjointSetsElement &realDestinationElement = sets[ realDestination ];

      if ( realSourceElement.rank <= realDestinationElement.rank ) {
        realSourceElement.parent = realDestination;
        realDestinationElement.size += realSourceElement.size;
        realSourceElement.size = 0;

        if ( realSourceElement.rank == realDestinationElement.rank ) {
          realDestinationElement.rank++;
        }

        if ( realDestinationElement.size > max_table_size ) {
          max_table_size = realDestinationElement.size;
        }
      } else {
        realDestinationElement.parent = realSource;

        realSourceElement.size += realDestinationElement.size;
        realDestinationElement.size = 0;
        if ( realSourceElement.size > max_table_size ) {
          max_table_size = realSourceElement.size;
        }
      }
    }
  }
};

int main() {
  int n, m;
  cin >> n >> m;

  DisjointSets tables( n );
  for (auto &table : tables.sets) {
    cin >> table.size;
    tables.max_table_size = max( tables.max_table_size, table.size );
  }

  for (int i = 0; i < m; i++) {
    int destination, source;
    cin >> destination >> source;

    tables.merge(destination - 1, source - 1);
    cout << tables.max_table_size << endl;
  }

  return 0;
}
