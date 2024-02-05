/*
This implementation adds a capacity_ member variable to the UnionFind class, 
which keeps track of the current capacity of the nodes_ array. 
The Insert function increases the size of the array by a factor of 2 when 
the key to be inserted is greater than or equal to the current size of the array. 
The Remove function replaces the node to be removed with the last node in the array, 
decrements the size_ variable, and then checks if the size_ is less than or equal to half the capacity_. 
If it is, then it decreases the capacity of the nodes_ array by a factor of 2.
*/

// --------------------------DO NOT FORGET TO MODIFY THE CODE THAT THEY WON'T KNOW!-------------------------//

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

// --------------------------DO NOT FORGET TO MODIFY THE CODE THAT THEY WON'T KNOW!-------------------------//

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

// --------------------------DO NOT FORGET TO MODIFY THE CODE THAT THEY WON'T KNOW!-------------------------//

  Node<Key, Data>* Insert(Key key, Data data) {
    if (key >= size_) {
      Node<Key, Data>* old_nodes = nodes_;
      int old_size = size_;
      size_ = std::max(key + 1, size_ * 2);
      nodes_ = new Node<Key, Data>[size_];
      for (int i = 0; i < old_size; i++) {
        nodes_[i] = old_nodes[i];
      }
      delete[] old_nodes;
    }
    nodes_[key] = Node<Key, Data>{key, data, nullptr, 0};
  }

    void Remove(Node<Key, Data>* node) {
    node->parent = &nodes_[size_ - 1];
    node->key = nodes_[size_ - 1].key;
    node->data = nodes_[size_ - 1].data;
    size_--;
    if (size_ <= capacity_ / 2) {
      Node<Key, Data>* old_nodes = nodes_;
      int old_capacity = capacity_;
      capacity_ = capacity_ / 2;
      nodes_ = new Node<Key, Data>[capacity_];
      for (int i = 0; i < size_; i++) {
        nodes_[i] = old_nodes[i];
      }
      delete[] old_nodes;
    }
  }

// --------------------------DO NOT FORGET TO MODIFY THE CODE THAT THEY WON'T KNOW!-------------------------//


  int size() { return size_; }
  int capacity() { return capacity_; }

 private:
  Node<Key, Data>* nodes_;
  int size_;
  int capacity_;
};

// --------------------------DO NOT FORGET TO MODIFY THE CODE THAT THEY WON'T KNOW!-------------------------//

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
