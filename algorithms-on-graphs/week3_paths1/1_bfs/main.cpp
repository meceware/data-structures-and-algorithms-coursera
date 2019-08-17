#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

struct VertexInfo {
  int distance;
  int previous;
};

int distance(vector<vector<int> > &adj, int s, int t) {
  if (s == t) {
    return 0;
  }

  unsigned int numberOfVertices = adj.size();
  vector<VertexInfo> info(numberOfVertices, {-1, -1});
  // Reset the main vertex difference
  info[s].distance = 0;

  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    const int u = q.front();
    q.pop();
    for (int i = 0; i < adj[u].size(); ++i) {
      const int w = adj[u][i];
      if (w == t) {
        return info[u].distance + 1;
      }

      if (info[w].distance == -1) {
        q.push(w);
        info[w].distance = info[u].distance + 1;
        info[w].previous = u;
      }
    }
  }

  return -1;
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
