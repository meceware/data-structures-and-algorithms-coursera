#include <iostream>
#include <vector>

using std::vector;

void dfs(const vector<vector<int> > &adj, vector<bool> &visited, int x) {
  visited[x] = true;
  for (int i = 0; i < adj[x].size(); ++i) {
    int w = adj[x][i];

    if (!visited[w]) {
      dfs(adj, visited, w);
    }
  }
}

int number_of_components(const vector<vector<int> > &adj) {
  // Set visited
  vector<bool> visited(adj.size(), false);

  int res = 0;
  for (int i = 0; i < adj.size(); ++i) {
    if (!visited[i]) {
      dfs(adj, visited, i);
      res++;
    }
  }

  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
