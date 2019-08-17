#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

struct Edge {
  int vertex;
  int cost;
};

struct Path {
  bool isReachable;
  bool isShortest;
  long long distance;
};

const long long infinity = std::numeric_limits<long long>::max();

void shortest_paths(const vector<vector<Edge> > &adj, const int s, vector<Path> &path) {
  const int tableSize = adj.size();

  path[s].isReachable = true;
  path[s].distance = 0;

  // First find the negative cycles and set them inside a queue
  queue<int> cycles;
  for (int i = 0; i < tableSize; ++i) {
    for (int j = 0; j < tableSize; ++j) {
      if (path[j].distance == infinity) {
        continue;
      }

      for (const auto& edge : adj[j]) {
        if (path[edge.vertex].distance > path[j].distance + edge.cost) {
          path[edge.vertex].distance = path[j].distance + edge.cost;
          path[edge.vertex].isReachable = true;
          // If distance keeps changing on the last iteration, there is a negative cycle
          if (i == tableSize - 1) {
            cycles.push(edge.vertex);
          }
        }

      }
    }
  }

  while (!cycles.empty()) {
    int w = cycles.front();
    cycles.pop();

    if (!path[w].isShortest) {
      continue;
    }

    queue<int> visiting;
    visiting.push(w);

    while (!visiting.empty()) {
      int u = visiting.front();
      visiting.pop();
      for (const auto& edge : adj[u]) {
        if (path[edge.vertex].isShortest) {
          visiting.push(edge.vertex);
          path[edge.vertex].isShortest = false;
        }
      }
    }
  }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<Edge> > adj(n, vector<Edge>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back({y - 1, w});
  }
  std::cin >> s;
  s--;
  vector<Path> path(n, {false, true, infinity});
  shortest_paths(adj, s, path);
  for (const auto& p : path) {
    if (!p.isReachable) {
      std::cout << "*\n";
    } else if (!p.isShortest) {
      std::cout << "-\n";
    } else {
      std::cout << p.distance << "\n";
    }
  }
}

/* Double negative cycles test input
9 10
4 5 1
4 1 2
1 2 1
2 3 2
3 1 -5
4 6 2
6 7 1
7 8 2
8 6 -5
8 9 1
4
-
-
0
1
-
-
-
-
*/
/*
4 5 1 2 1 2 3 1 3 1 -3 3 4 1 4 3 1 4
-
-
-
-
*/