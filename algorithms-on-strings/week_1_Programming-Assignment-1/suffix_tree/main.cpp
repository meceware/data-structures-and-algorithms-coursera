#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Node {
  using NodeArray = std::shared_ptr<vector<Node>>;

  int start;
  int size;
  NodeArray next;

  Node(int start = 0, int size = 0, NodeArray nextNodes = nullptr) : start(start), size(size), next(nextNodes) {
    if (!next) {
      generateNext();
    }
  }

  void generateNext() {
    next = std::make_shared<vector<Node>>();
  }
};

void buildTree(Node& root, const string& text, const int index) {
  const int textSize = text.size();

  for (unsigned int i = 0; i < root.next->size(); ++i) {
    Node& nextNode = root.next->at(i);
    int start = nextNode.start;
    int size = nextNode.size;

    // Get common string length
    int common = 0;
    while ( (index + common < textSize) && (common < size) && (text[index + common] == text[start + common]) ) {
      common++;
    }

    if (common == size) {
      // std::cout << "common is size: " << index + common << std::endl;
      buildTree(nextNode, text, index + common);
      return;
    }

    if (common > 0 && common < size) {
      // std::cout << "adding middle size: " << common << " start: " << start + common << " size: " << size - common << " start: " << index + common << " size: " << textSize - index - common << std::endl;
      nextNode.size = common;
      auto oldNext = nextNode.next;
      nextNode.generateNext();
      nextNode.next->emplace_back(start + common, size - common, oldNext);
      nextNode.next->emplace_back(index + common, textSize - index - common);
      return;
    }

    if (common == 0 && i == root.next->size() - 1) {
      // std::cout << "adding root in start: " << index << " size: " << textSize - index << std::endl;
      break;
    }
  }

  // std::cout << "adding root start: " << index << " size: " << textSize - index << std::endl;
  root.next->emplace_back(index, textSize - index);
}

void getNodes(const Node& root, const string& text, vector<string> &edges) {
  const vector<Node>& nodes = *root.next;
  for (const auto& node : nodes) {
    edges.push_back(text.substr(node.start, node.size));
    getNodes(node, text, edges);
  }
}

vector<string> ComputeSuffixTreeEdges(const string& text) {

  Node root;
  unsigned int len = text.size();
  for (unsigned int i = 0; i < len; ++i) {
    buildTree(root, text, i);
  }

  vector<string> edges;
  getNodes(root, text, edges);

  return edges;
}

int main() {
  string text;
  cin >> text;

  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (const auto& edge : edges) {
    cout << edge << endl;
  }

  return 0;
}
