#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <limits>

using std::string;
using std::vector;

const int INFINITY_INT = std::numeric_limits<int>::max();

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

struct Path {
  const Node& node;
  string sub;

  Path(const Node& node, string sub = "") : node(node), sub(sub) {}
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

void createTree(const string& text, Node& root) {
  unsigned int len = text.size();
  for (unsigned int i = 0; i < len; ++i) {
    buildTree(root, text, i);
  }
}

bool isNonShared(const Node& node, const int pSize) {
  if (node.start > pSize) {
    return false;
  }

  if (node.next->empty()) {
    return true;
  }

  for (const auto& children : *node.next) {
    if (!isNonShared(children, pSize)) {
      return false;
    }
  }

  return true;
}

string solve (string p, string q) {
  const int pSize = p.size();
  const string text = p + "#" + q + "$";

  // Build suffix tree
  Node root;
  createTree(text, root);

  // Search
  std::queue<Path> nodeQ;
  nodeQ.emplace(root);

	string result = p;
  while (!nodeQ.empty()) {
    const Path path = nodeQ.front();
    nodeQ.pop();

    for (const auto& child : *(path.node.next)) {
      if (child.start != pSize) {
        if (isNonShared(child, pSize)) {
          string sub = path.sub + text[child.start];
          if (sub.size() < result.size()) {
            result = sub;
          }
        } else {
          nodeQ.emplace(child, path.sub + text.substr(child.start, child.size));
        }
      }
    }
  }

	return result;
}

int main (void) {
	string p;
	std::cin >> p;
	string q;
	std::cin >> q;

	std::cout << solve (p, q) << std::endl;

	return 0;
}
