#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using std::vector;
using std::priority_queue;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
struct Node {
  int node;
  int cost;
};

template <typename T>
struct Direction {
  T forward;
  T backward;
};

typedef Direction< vector< vector<Node> > > Adj;

// Distances can grow out of int type
typedef long long Len;
typedef std::pair<Len, int> Edge;

// Each priority queue stores the closest unprocessed node in its head.
typedef priority_queue<Edge, vector<Edge>, std::greater<Edge> > Queue;

const Len INFINITY = std::numeric_limits<Len>::max() >> 2; // divided by 4

class Bidijkstra {
    // Graph adj_[0] and cost_[0] correspond to the initial graph,
    // adj_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding
    // to nodes.
    // Adjacency list itself is stored in adj_, and the corresponding
    // edge costs are stored in cost_.
    const Adj &adj;
    // Stores distances for the forward/backward search.
    Direction<vector<Len>> distance;
    // Stores all the nodes visited either by forward or backward search.
    vector<int> workset;
    // Stores a flag for each node which is True iff the node was visited
    // either by forward or backward search.
    Direction<vector<bool>> visited;

public:
  Bidijkstra(int n, const Adj &adj) : adj(adj) {
    distance.forward.resize(n, INFINITY);
    distance.backward.resize(n, INFINITY);

    visited.forward.resize(n, false);
    visited.backward.resize(n, false);

    workset.reserve(n);
  }

  // Initialize the data structures before new query,
  // clear the changes made by the previous query.
  void clear() {
    std::fill(distance.forward.begin(), distance.forward.end(), INFINITY);
    std::fill(distance.backward.begin(), distance.backward.end(), INFINITY);
    for (const auto v : workset) {
      visited.forward[v] = visited.backward[v] = false;
    }
    workset.clear();
  }

  // Processes visit of either forward or backward search
  // (determined by value of side), to node v trying to
  // relax the current distance by dist.
  template <typename T>
  void visit(Queue& q, T &distance, int v, Len dist) {
    if (distance[v] > dist) {
      distance[v] = dist;
      q.push({dist, v});
    }
  }

  Len getShortDistance() {
    Len dist = INFINITY;
    for (const auto& w : workset) {
      Len current = distance.forward[w] + distance.backward[w];
      dist = (current < dist) ? current : dist;
    }

    return dist == INFINITY ? -1 : dist;
  }

  // Returns the distance from s to t in the graph.
  Len query(int s, int t) {
    clear();
    Queue forwardQ;
    Queue backwardQ;
    visit(forwardQ, distance.forward, s, 0);
    visit(backwardQ, distance.backward, t, 0);

    while (!forwardQ.empty() && !backwardQ.empty()) {
      int vFront = forwardQ.top().second;
      forwardQ.pop();
      for (const auto& edge : adj.forward[vFront]) {
        visit(forwardQ, distance.forward, edge.node, distance.forward[vFront] + edge.cost);
      }
      workset.push_back(vFront);
      visited.forward[vFront] = true;
      if (visited.backward[vFront]) {
        break;
      }

      // Backwa
      int vBack = backwardQ.top().second;
      backwardQ.pop();
      for (const auto& edge : adj.backward[vBack]) {
        visit(backwardQ, distance.backward, edge.node, distance.backward[vBack] + edge.cost);
      }
      workset.push_back(vBack);
      visited.backward[vBack] = true;
      if (visited.forward[vBack]) {
        break;
      }
    }

    return getShortDistance();
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Adj adj;
  adj.forward.resize(n);
  adj.backward.resize(n);

  for (int i = 0; i < m; ++i) {
    int u, v, c;
    std::cin >> u >> v >> c;
    adj.forward[u - 1].push_back({v - 1, c});
    adj.backward[v - 1].push_back({u - 1, c});
  }

  Bidijkstra bidij(n, adj);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) {
    int u, v;
    std::cin >> u >> v;
    std::cout << bidij.query(u - 1, v - 1) << std::endl;
  }
}
