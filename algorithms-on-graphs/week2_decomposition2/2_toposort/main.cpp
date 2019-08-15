#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

void dfs(const vector<vector<int> > &adj, vector<int> &order, vector<bool> &visited, int x) {
  visited[x] = true;

  for (unsigned int j = adj[x].size(); j > 0; --j) {
    int w = adj[x][j - 1];
    if (!visited[w]) {
      dfs(adj, order, visited, w);
    }
  }

  order.push_back(x);
}

vector<int> toposort(vector<vector<int> > adj) {
  unsigned int adjSize = adj.size();
  vector<int> order;
  vector<bool> visited(adjSize, false);

  for (unsigned int i = adjSize; i > 0; --i) {
    if (!visited[i - 1]) {
      dfs(adj, order, visited, i - 1);
    }
  }

  return order;
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
  vector<int> order = toposort(adj);
  for (size_t i = order.size(); i > 0; --i) {
    std::cout << order[i - 1] + 1 << " ";
  }
}
