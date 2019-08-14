#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

struct Vertex {
  char key;
  long long index;
  Vertex* left;
  Vertex* right;
  Vertex* parent;

  Vertex(char key, long long index, Vertex* left, Vertex* right, Vertex* parent)
    : key(key), index(index), left(left), right(right), parent(parent) {}
};

class Rope {
private:
  std::vector<char> s;
  Vertex* root;

  void update(Vertex* v) {
    if (v == NULL) {
      return;
    }

    if (v->left != NULL) {
      v->left->parent = v;
    }
    if (v->right != NULL) {
      v->right->parent = v;
    }
  }

  void small_rotation(Vertex* v) {
    Vertex* parent = v->parent;

    if (parent == NULL) {
      return;
    }

    Vertex* grandparent = v->parent->parent;
    if (parent->left == v) {
      Vertex* m = v->right;
      v->right = parent;
      parent->left = m;
    } else {
      Vertex* m = v->left;
      v->left = parent;
      parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL) {
      if (grandparent->left == parent) {
        grandparent->left = v;
      } else {
        grandparent->right = v;
      }
    }
  }

  void big_rotation(Vertex* v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
      // Zig-zig
      small_rotation(v->parent);
      small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
      // Zig-zig
      small_rotation(v->parent);
      small_rotation(v);
    } else {
      // Zig-zag
      small_rotation(v);
      small_rotation(v);
    }
  }

  void splay(Vertex*& root, Vertex* v) {
    if (v == NULL) {
      return;
    }

    while (v->parent != NULL) {
      if (v->parent->parent == NULL) {
        small_rotation(v);
        break;
      }
      big_rotation(v);
    }
    root = v;
  }

  Vertex* find(Vertex* root, long long index) {
    Vertex* v = root;
    Vertex* last = root;
    Vertex* next = NULL;
    while (v != NULL) {
      if (v->index >= index && (next == NULL || v->index < next->index)) {
        next = v;
      }
      last = v;
      if (v->index == index) {
        break;
      }
      if (v->index < index) {
        v = v->right;
      } else {
        v = v->left;
      }
    }
    splay(root, last);
    return next;
  }

  void split(Vertex*& root, long long index, Vertex*& left, Vertex*& right) {
    right = find(root, index);
    splay(root, right);
    if (right == NULL) {
      left = right;
      return;
    }
    left = right->left;
    right->left = NULL;
    if (left != NULL) {
      left->parent = NULL;
    }
    update(left);
    update(right);
  }

  Vertex* merge(Vertex* left, Vertex* right) {
    if (left == NULL) {
      return right;
    }
    if (right == NULL) {
      return left;
    }
    Vertex* min_right = right;
    while (min_right->left != NULL) {
      min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
  }

  void insert(char c, long long index) {
    Vertex* left = NULL;
    Vertex* right = NULL;
    Vertex* new_vertex = NULL;
    split(root, index, left, right);
    if (right == NULL || right->key != c) {
      new_vertex = new Vertex(c, index, NULL, NULL, NULL);
    }

    root = merge( root, merge( merge(left, new_vertex), right ) );
  }

  Vertex* erase(long long index) {
    Vertex* v = find(root, index);
    splay(root, v);

    if (v == NULL || v->index != index) {
      return NULL;
    }

    root = merge(v->left, v->right);
    if (root) {
      root->parent = NULL;
    }

    return v;
  }

  void orderRecursive(Vertex* root){
    if (root == NULL) {
      return;
    }

    if (root->left != NULL) {
      orderRecursive(root->left);
    }

    root->index = s.size(); // indices updated each time
    s.push_back(root->key);

    if (root->right != NULL){
      orderRecursive(root->right);
    }
  }

  void orderRecursiveRightIndex(Vertex* v, int subSize){
    if (v == NULL) {
      return;
    }

    if (v->left != NULL) {
      orderRecursive(v->left);
    }

    v->index += subSize;

    if (v->right != NULL){
      orderRecursive(v->right);
    }
  }

public:
  Rope(const std::string &str) : root(NULL) {
    for (int i = 0; i < str.length(); ++i) {
      insert(str[i], i);
    }
  }

  void process( int i, int j, int k ) {
    Vertex* left = NULL;
    Vertex* right = NULL;

    std::vector<char> sub;

    for(int x = i; x <= j; ++x) {
      Vertex* er = erase(x);
      sub.push_back(er->key);
    }

    // indices changed, recalculate
    s.clear();
    orderRecursive(root);

    for(int it = 0; it < sub.size(); ++it) {
      if (s.size() > k) {
        split(root, (long long)k + it, left, right);

        orderRecursiveRightIndex(right, sub.size());

        Vertex* new_vertex = new Vertex(sub[it], (long long)k + it, NULL, NULL, NULL);

        if (right == NULL && left == NULL) {
					// the case where the split was smooth
					root = merge(root, new_vertex);
				} else {
					root = merge(merge(left, new_vertex), right);
        }
      } else {
        Vertex* new_vertex = new Vertex(sub[it], (long long)k + it, NULL, NULL, NULL);
        root = merge(root, new_vertex);
      }

      s.clear();
      orderRecursive(root);
    }
  }

  std::string result() {
    return std::string(s.begin(), s.end());
  }
};

int main() {
  // std::ios_base::sync_with_stdio(0);
  std::string s;
  std::cin >> s;
  Rope rope(s);
  int actions;
  std::cin >> actions;

  for (int action_index = 0; action_index < actions; ++action_index) {
    int i, j, k;
    std::cin >> i >> j >> k;
    rope.process(i, j, k);
  }

  std::cout << rope.result() << std::endl;
}
