#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;

struct PriorityPair {
  int job;
  long long priority;
};

class JobQueue {
 private:
  int num_workers;
  vector<int> jobs;

  vector<int> assigned_workers;
  vector<long long> start_times;

  void WriteResponse() const {
    for (int i = 0; i < jobs.size(); ++i) {
      cout << assigned_workers[i] << " " << start_times[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers >> m;
    jobs.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs[i];
  }

  void ChangePriority( vector< PriorityPair > &priorityQueue, int index, const long long priority ) {
    const auto getParent = []( int i ) -> int {
      return ( i - 1 ) / 2;
    };

    const auto getLeftChild = []( int i ) -> int {
      return 2 * i + 1;
    };

    const auto getRightChild = []( int i ) -> int {
      return 2 * (i + 1);
    };

    const auto compareChildren = []( const PriorityPair &left, const PriorityPair &right ) -> bool {
      return left.priority == right.priority ?
        left.job < right.job : left.priority < right.priority;
    };

    const int size = priorityQueue.size();

    const auto getMinOfChild = [ &priorityQueue, size, &getLeftChild, &getRightChild, &compareChildren ]( int i ) {
      int leftChild = getLeftChild( i );
      int rightChild = getRightChild( i );

      i = ( leftChild < size ) && compareChildren( priorityQueue[ leftChild ], priorityQueue[ i ] ) ? leftChild : i;
      i = ( rightChild < size ) && compareChildren( priorityQueue[ rightChild ], priorityQueue[ i ] ) ? rightChild : i;

      return i;
    };

    const long long oldPriority = priorityQueue[ index ].priority;
    priorityQueue[ index ].priority = priority;
    if ( priority < oldPriority ) {
      // sift up
      while ( index > 0 && compareChildren( priorityQueue[ index ], priorityQueue[ getParent( index ) ] ) ) {
        int parent = getParent( index );
        swap( priorityQueue[ index ], priorityQueue[ parent ] );
        index = parent;
      }
    } else {
      // sift down
      int minIndex;
      while ( index != ( minIndex = getMinOfChild( index ) ) ) {
        swap( priorityQueue[ index ], priorityQueue[ minIndex ] );

        index = minIndex;
      }
    }
  }

  void AssignJobs() {
    assigned_workers.resize( jobs.size() );
    start_times.resize( jobs.size() );

    vector< PriorityPair > priorityQueue;
    priorityQueue.reserve( num_workers );
    for ( int i = 0; i < num_workers; i++ ) {
      priorityQueue.push_back( { i, 0 } );
    }

    int jobsSize = jobs.size();
    for ( int i = 0; i < jobsSize; ++i ) {
      assigned_workers[i] = priorityQueue[0].job;
      start_times[i] = priorityQueue[0].priority;
      ChangePriority( priorityQueue, 0, jobs[ i ] + priorityQueue[0].priority );
    }

#ifdef _NAIVE
    // TODO: replace this code with a faster algorithm.
    assigned_workers.resize(jobs.size());
    start_times.resize(jobs.size());
    vector<long long> next_free_time(num_workers, 0);
    for (int i = 0; i < jobs.size(); ++i) {
      int duration = jobs[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers[i] = next_worker;
      start_times[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
#endif
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
