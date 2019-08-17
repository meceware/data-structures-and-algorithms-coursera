#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
  unsigned int numberOfVertices = adj.size();
  vector<int> colors(numberOfVertices, -1);
  // Reset the color for the first
  colors[0] = 0;

  // Create the queue and initialize with the first vertex
  queue<int> q;
  q.push(0);

  while (!q.empty()) {
    const int u = q.front();
    q.pop();

    for (int i = 0; i < adj[u].size(); ++i) {
      const int w = adj[u][i];

      if (colors[w] == -1) {
        q.push(w);
        colors[w] = (colors[u] + 1) % 2;
      } else if (colors[w] == colors[u]) {
        return 0;
      }
    }
  }

  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
