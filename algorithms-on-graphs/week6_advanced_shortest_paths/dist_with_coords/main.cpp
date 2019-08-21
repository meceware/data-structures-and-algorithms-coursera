#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>

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
typedef std::pair<Len, int> LenPair;
typedef std::pair<Len, Len> Coordinate;
typedef vector<Coordinate> Coordinates;

// Each priority queue stores the closest unprocessed node in its head.
typedef priority_queue<LenPair, vector<LenPair>, std::greater<LenPair> > Queue;

const Len LLINFINITY = std::numeric_limits<Len>::max() >> 2; // divided by 4

class AStar {
    // Graph adj_[0] and cost_[0] correspond to the initial graph,
    // adj_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding
    // to nodes.
    // Adjacency list itself is stored in adj_, and the corresponding
    // edge costs are stored in cost_.
    const Adj &adj;
    const Coordinates &coordinates;
    // Stores distances for the forward/backward search.
    vector<Len> distance;
    vector<Len> potentials;
    // Stores all the nodes visited either by forward or backward search.
    vector<int> workset;
    // Stores a flag for each node which is True iff the node was visited
    // either by forward or backward search.
    vector<bool> visited;

public:
  AStar(int n, const Adj &adj, const Coordinates& coordinates) : adj(adj), coordinates(coordinates), distance(n, LLINFINITY), potentials(n, -1), visited(n, false) {
    workset.reserve(n);
  }

  // Initialize the data structures before new query,
  // clear the changes made by the previous query.
  void clear() {
    for (const auto v : workset) {
      distance[v] = LLINFINITY;
      visited[v] = false;
      potentials[v] = -1;
    }
    workset.clear();
  }

  // Processes visit of either forward or backward search
  // (determined by value of side), to node v trying to
  // relax the current distance by dist.
  void visit(Queue& q, int v, Len dist, Len pot) {
    if (distance[v] > dist) {
      distance[v] = dist;
      q.push({dist + pot, v});
      workset.push_back(v);
    }
  }

  int extractMin(Queue& q) {
    const auto p = q.top();
    q.pop();
    return p.second;
  }

  Len convertShortDistance(Len dist) {
    return dist == LLINFINITY ? -1 : dist;
  }

  Len getPotential(int s, int t) {
    if (potentials[s] == -1) {
      potentials[s] = hypot(coordinates[s].first - coordinates[t].first, coordinates[s].second - coordinates[t].second);
    }

    return potentials[s];
  }

  // Returns the distance from s to t in the graph.
  Len query(int s, int t) {
    clear();
    Queue q;
    visit(q, s, 0, getPotential(s, t));

    while (!q.empty()) {
      int v = extractMin(q);

      if (v == t) {
        return convertShortDistance(distance[v]);
      }

      if (!visited[v]) {
        for (const auto& edge : adj.forward[v]) {
          if (!visited[edge.node]) {
            visit(q, edge.node, distance[v] + edge.cost, getPotential(edge.node, t));
          }
        }
        visited[v] = true;
      }
    }

    return -1;
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Coordinates coordinates;
  coordinates.resize(n);
  for (unsigned int i = 0; i < n; ++i) {
    std::cin >> coordinates[i].first >> coordinates[i].second;
  }

  Adj adj;
  adj.forward.resize(n);

  for (int i = 0; i < m; ++i) {
    int u, v, c;
    std::cin >> u >> v >> c;
    adj.forward[u - 1].push_back({v - 1, c});
  }

  AStar astar(n, adj, coordinates);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) {
    int u, v;
    std::cin >> u >> v;
    std::cout << astar.query(u-1, v-1) << std::endl;
  }
}
