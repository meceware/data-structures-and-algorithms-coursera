#include <iostream>
#include <vector>
#include <limits>

using std::vector;

struct Edge {
  int vertex;
  int cost;
};

int negative_cycle(const vector<vector<Edge> > &adj) {
  const int infinity = std::numeric_limits<int>::max();
  const int tableSize = adj.size();
  vector<long long> distance(tableSize, infinity);
  distance[0] = 0;

  for (int i = 0; i < tableSize; ++i) {
    for (int j = 0; j < tableSize; ++j) {

      for (const auto& edge : adj[j]) {
        if (distance[edge.vertex] > distance[j] + edge.cost) {
          distance[edge.vertex] = distance[j] + edge.cost;
          // If distance keeps changing on the last iteration, there is a negative cycle
          if (i == tableSize - 1) {
            return 1;
          }
        }

      }
    }
  }

  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<Edge> > adj(n, vector<Edge>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back({y - 1, w});
  }
  std::cout << negative_cycle(adj);
}
