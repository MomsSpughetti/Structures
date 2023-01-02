/*
No STL
Supports insert and remove
Has Union and Find functions!
*/

#include <iostream>

template <typename Key, typename Data>
struct Node {
  Key key;
  Data data;
  Node* parent;
  int rank;
};

template <typename Key, typename Data>
class UnionFind {
 public:
  UnionFind(int size) : size_(size), nodes_(new Node<Key, Data>[size]) {
    for (int i = 0; i < size; i++) {
      nodes_[i] = Node<Key, Data>{i, Data(), nullptr, 0};
    }
  }

  ~UnionFind() { delete[] nodes_; }

  Node<Key, Data>* Find(Node<Key, Data>* x) {
    if (x->parent == nullptr) {
      return x;
    }
    x->parent = Find(x->parent);
    return x->parent;
  }

  void Union(Node<Key, Data>* x, Node<Key, Data>* y) {
    Node<Key, Data>* x_root = Find(x);
    Node<Key, Data>* y_root = Find(y);
    if (x_root == y_root) return;
    if (x_root->rank < y_root->rank) {
      x_root->parent = y_root;
    } else if (x_root->rank > y_root->rank) {
      y_root->parent = x_root;
    } else {
      y_root->parent = x_root;
      x_root->rank++;
    }
  }

  Node<Key, Data>* Find(Key key) {
    return Find(&nodes_[key]);
  }

  Node<Key, Data>* Insert(Key key, Data data) {
    if (key >= size_) {
      Node<Key, Data>* old_nodes = nodes_;
      int old_size = size_;
      size_ = key + 1;
      nodes_ = new Node<Key, Data>[size_];
      for (int i = 0; i < old_size; i++) {
        nodes_[i] = old_nodes[i];
      }
      delete[] old_nodes;
    }
    nodes_[key] = Node<Key, Data>{key, data, nullptr, 0};
    return &nodes_[key];
  }

  void Remove(Node<Key, Data>* node) {
    node->parent = &nodes_[size_ - 1];
    node->key = nodes_[size_ - 1].key;
    node->data = nodes_[size_ - 1].data;
    size_--;
  }

  int size() { return size_; }

 private:
  Node<Key, Data>* nodes_;
  int size_;
};

int main() {
  UnionFind<int, std::string> uf(10);
  Node<int, std::string>* node0 = uf.Insert(0, "node 0");
  Node<int, std::string>* node1 = uf.Insert(1, "node 1");
  Node<int, std::string>* node2 = uf.Insert(2, "node 2");
  Node<int, std::string>* node3 = uf.Insert(3, "node 3");
  uf.Union(node0, node1);
  uf.Union(node2, node3);
  uf.Union(node0, node3);

  std::cout << uf.Find(0)->key << std::endl;
  std::cout << uf.Find(1)->key << std::endl;
  std::cout << uf.Find(2)->key << std::endl;
  std::cout << uf.Find(3)->key << std::endl;

  uf.Remove(node1);

  std::cout << uf.Find(0)->key << std::endl;
  std::cout << uf.Find(1)->key << std::endl;
  std::cout << uf.Find(2)->key << std::endl;
  std::cout << uf.Find(3)->key << std::endl;

  return 0;
}
