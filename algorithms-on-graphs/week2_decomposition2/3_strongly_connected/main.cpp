#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

void dfs(const vector<vector<int> > &adj, vector<bool> &visited, stack<int> *fillStack, int x) {
  visited[x] = true;

  for (unsigned int j = 0; j < adj[x].size(); ++j) {
    const int w = adj[x][j];
    if (!visited[w]) {
      dfs(adj, visited, fillStack, w);
    }
  }

  if (fillStack) {
    fillStack->push(x);
  }
}

void reverseEdges(const vector<vector<int> > &adj, vector<vector<int> > &adjReverse) {
  unsigned int adjSize = adj.size();
  for (unsigned int i = 0; i < adjSize; ++i) {
    for (unsigned int j = 0; j < adj[i].size(); ++j) {
      const int w = adj[i][j];
      adjReverse[w].push_back(i);
    }
  }
}

int number_of_strongly_connected_components(const vector<vector<int> > &adj) {
  const unsigned int adjSize = adj.size();
  vector<bool> visited(adjSize, false);
  stack<int> fillStack;

  vector<vector<int> > adjReverse(adjSize, vector<int>());
  reverseEdges(adj, adjReverse);

  // Run DFS
  for (unsigned int i = 0; i < adjSize; ++i) {
    if (!visited[i]) {
      dfs(adj, visited, &fillStack, i);
    }
  }

  std::fill(visited.begin(), visited.end(), false);

  int result = 0;
  while (!fillStack.empty()) {
    const int x = fillStack.top();
    fillStack.pop();

    if (!visited[x]) {
      dfs(adjReverse, visited, nullptr, x);
      result++;
    }
  }

  return result;
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
  std::cout << number_of_strongly_connected_components(adj);
}