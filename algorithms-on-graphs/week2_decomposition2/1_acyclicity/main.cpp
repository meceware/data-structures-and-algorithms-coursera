#include <iostream>
#include <vector>

using std::vector;

int acyclic(const vector<vector<int> > &adj, vector<bool> &visited, vector<bool> &track, const unsigned int index) {
  if (!visited[index]) {
    visited[index] = true;
    track[index] = true;

    for (unsigned int j = 0; j < adj[index].size(); ++j) {
      int w = adj[index][j];

      if (!visited[w]) {
        if (acyclic(adj, visited, track, w)) {
          return 1;
        }
      }

      if (track[w]) {
        return 1;
      }
    }
  }

  track[index] = false;
  return 0;
}

int acyclic(const vector<vector<int> > &adj) {
  unsigned int adjSize = adj.size();
  vector<bool> visited(adjSize);
  vector<bool> track(adjSize);

  for (unsigned int i = 0; i < adjSize; ++i) {
    if (acyclic(adj, visited, track, i)) {
      return 1;
    }
  }

  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
