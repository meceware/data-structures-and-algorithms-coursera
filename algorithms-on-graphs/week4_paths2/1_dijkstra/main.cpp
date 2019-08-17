#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::priority_queue;

struct Edges{
  int vertex;
  int cost;
};

struct Node {
  int vertex;
  int distance;
};

int distance(const vector< vector<Edges> > &adj, const int s, const int t) {
  const int infinity = std::numeric_limits<int>::max();
  vector<int> dist(adj.size(), infinity);
  dist[s] = 0;

  const auto cmp = [](const Node& a, const Node& b) {
    return a.distance > b.distance;
  };
  priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
  pq.push({s, 0});

  while (!pq.empty()) {
    const Node n = pq.top();
    pq.pop();

    for (int i = 0; i < adj[n.vertex].size(); ++i) {
      const Edges& w = adj[n.vertex][i];
      if (dist[w.vertex] > dist[n.vertex] + w.cost) {
        dist[w.vertex] = dist[n.vertex] + w.cost;
        pq.push({w.vertex, dist[w.vertex]});
      }
    }
  }

  return dist[t] == infinity ? -1 : dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector< vector<Edges> > adj(n, vector<Edges>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back({y - 1, w});
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
