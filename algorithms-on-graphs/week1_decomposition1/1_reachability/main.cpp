#include <iostream>
#include <vector>

using std::vector;

int dfs(const vector<vector<int> > &adj, vector<bool> &visited, const int x, const int y) {
  if (x == y) {
    return 1;
  }

  visited[x] = true;

  for (int i = 0; i < adj[x].size(); ++i) {
    int w = adj[x][i];

    if (!visited[w]) {
      if (dfs(adj, visited, w, y)) {
        return 1;
      }
    }
  }

  return 0;
}

int reach(const vector<vector<int> > &adj, const int x, const int y) {
  if (x == y) {
    return 1;
  }

  // Set visited
  vector<bool> visited(adj.size(), false);

  return dfs(adj, visited, x, y);
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector< vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
