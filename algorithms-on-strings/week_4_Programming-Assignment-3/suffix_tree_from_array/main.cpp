#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

using std::make_pair;
using std::map;
using std::pair;
using std::string;
using std::vector;

const map<char, int> Alphabet{ {'$', 0}, {'A', 1}, {'C', 2}, {'G', 3}, {'T', 4} };
const unsigned int AlpabetSize = Alphabet.size();

// Data structure to store edges of a suffix tree.
struct Edge {
  // The ending node of this edge.
  int node;
  // Depth
  int depth;
  // Starting position of the substring of the text corresponding to the label of this edge.
  int start;
  // Position right after the end of the substring of the text corresponding to the label of this edge.
  int end;


  Edge(int node, int depth, int start, int end) : node(node), depth(depth), start(start), end(end) {}
  Edge(const Edge& e) : node(e.node), depth(e.depth), start(e.start), end(e.end) {}
};

Edge CreateEdge(const Edge& edge, const int newNode, const int suffix, map<int, vector<Edge> > &tree, const int textSize)
{
    Edge newEdge{newNode, textSize - suffix, suffix + edge.depth, textSize};
    tree[edge.node].push_back(newEdge);

    return newEdge;
}

Edge BreakEdge(const Edge& edge, const int newNode, const int start, const int offset, map<int, vector<Edge> > &tree)
{
  Edge mid{newNode, edge.depth + offset, start, start + offset};

  // update the given edges starting position.
  tree[edge.node].back().start += offset;

  // the last edge from the ending node is now a child of the new node.
  tree[newNode] = vector<Edge>();
  tree[newNode].push_back(tree[edge.node].back());

  // the new edge is now a child of the previous node.
  tree[edge.node].pop_back();
  tree[edge.node].push_back(mid);

  return mid;
}

// Build suffix tree of the string text given its suffix array suffixArray
// and LCP array lcpArray. Return the tree as a mapping from a node ID
// to the vector of all outgoing edges of the corresponding node. The edges in the
// vector must be sorted in the ascending order by the first character of the edge label.
// Root must have node ID = 0, and all other node IDs must be different
// nonnegative integers.
//
// For example, if text = "ACACAA$", an edge with label "$" from root to a node with ID 1
// must be represented by Edge(1, 6, 7). This edge must be present in the vector tree[0]
// (corresponding to the root node), and it should be the first edge in the vector
// (because it has the smallest first character of all edges outgoing from the root).
map<int, vector<Edge>> SuffixTreeFromSuffixArray(const vector<int>& suffixArray, const vector<int>& lcpArray, const string& text) {
  const int textSize = text.size();

  map<int, vector<Edge> > tree;
  tree[0] = vector<Edge>();

  vector<int> path;
  Edge root{0, 0, -1, -1};
  Edge current = root;
  int lcpPrev = 0;
  int nodeCounter = 1;

  for (int i = 0; i < textSize; ++i) {
    int suffix = suffixArray[i];

    while (current.depth > lcpPrev) {
      path.pop_back();
      current = path.empty() ? root : tree[path.back()].back();
    }

    path.push_back(current.node);
    Edge& newEdge = current;

    if (current.depth != lcpPrev) {
      int start = suffixArray[i - 1] + current.depth;
      int offset = lcpPrev - current.depth;

      Edge mid = BreakEdge(current, nodeCounter, start, offset, tree);
      nodeCounter++;
      path.push_back(mid.node);

      newEdge = mid;
    }

    current = CreateEdge(newEdge, nodeCounter, suffix, tree, textSize);
    nodeCounter++;

    if (i < lcpArray.size()) {
      lcpPrev = lcpArray[i];
    }
  }

  return tree;
}


int main() {
  string text;
  std::cin >> text;

  const unsigned int textSize = text.size();

  vector<int> suffixArray(textSize);
  for (int i = 0; i < textSize; ++i) {
    std::cin >> suffixArray[i];
  }

  vector<int> lcpArray(textSize - 1);
  for (int i = 0; i + 1 < textSize; ++i) {
    std::cin >> lcpArray[i];
  }

  // Build the suffix tree and get a mapping from suffix tree node ID to the list of outgoing Edges.
  map<int, vector<Edge>> tree = SuffixTreeFromSuffixArray(suffixArray, lcpArray, text);
  std::cout << text << std::endl;
  // Output the edges of the suffix tree in the required order.
  // Note that we use here the contract that the root of the tree
  // will have node ID = 0 and that each vector of outgoing edges
  // will be sorted by the first character of the corresponding edge label.
  //
  // The following code avoids recursion to avoid stack overflow issues.
  // It uses a stack to convert recursive function to a while loop.
  // The stack stores pairs (node, edge_index).
  // This code is an equivalent of
  //
  //    OutputEdges(tree, 0);
  //
  // for the following _recursive_ function OutputEdges:
  //
  // void OutputEdges(map<int, vector<Edge> > tree, int node_id) {
  //   const vector<Edge>& edges = tree[node_id];
  //   for (int edge_index = 0; edge_index < edges.size(); ++edge_index) {
  //     printf("%d %d\n", edges[edge_index].start, edges[edge_index].end);
  //     OutputEdges(tree, edges[edge_index].node);
  //   }
  // }
  //
  vector<pair<int, int> > stack(1, make_pair(0, 0));
  while (!stack.empty()) {
    pair<int, int> p = stack.back();
    stack.pop_back();

    int node = p.first;
    if (!tree.count(node)) {
      continue;
    }

    int edge_index = p.second;

    const vector<Edge>& edges = tree[node];
    if (edge_index + 1 < edges.size()) {
      stack.push_back(make_pair(node, edge_index + 1));
    }

    std::cout << edges[edge_index].start << " " << edges[edge_index].end << std::endl;
    stack.push_back(make_pair(edges[edge_index].node, 0));
  }

  return 0;
}
