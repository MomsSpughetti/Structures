/*
Hash table

supports size changing!

*/

#include <iostream>

template <typename K, typename V>
class HashTable {
 public:
  HashTable(int size = 16) : size_(size), table_(new Node*[size]()) {}
  ~HashTable() {
    for (int i = 0; i < size_; i++) {
      auto *node = table_[i];
      while (node) {
        auto *temp = node;
        node = node->next;
        delete temp;
      }
    }
    delete[] table_;
  }

  void put(K key, V value) {
    int index = hash(key) % size_;
    auto *node = table_[index];
    while (node) {
      if (node->key == key) {
        node->value = value;
        return;
      }
      node = node->next;
    }
    node = new Node{key, value};
    node->next = table_[index];
    table_[index] = node;
    if (++count_ > size_) {
      resize(size_ * 2);
    }
  }

  V get(K key) {
    int index = hash(key) % size_;
    auto *node = table_[index];
    while (node) {
      if (node->key == key) {
        return node->value;
      }
      node = node->next;
    }
    return V{};
  }

  void remove(K key) {
    int index = hash(key) % size_;
    auto *node = table_[index];
    if (node && node->key == key) {
      table_[index] = node->next;
      delete node;
      if (--count_ < size_ / 4) {
        resize(size_ / 2);
      }
      return;
    }
    while (node) {
      if (node->next && node->next->key == key) {
        auto *temp = node->next;
        node->next = temp->next;
        delete temp;
        if (--count_ < size_ / 4) {
          resize(size_ / 2);
        }
        return;
      }
      node = node->next;
    }
  }

  bool contains(K key) {
    int index = hash(key) % size_;
    auto *node = table_[index];
    while (node) {
      if (node->key == key) {
        return true;
      }
      node = node->next;
    }
    return false;
  }

  int size() {
    return count_;
  }

 private:
  int size_;
  int count_ = 0;

  struct Node {
    K key;
    V value;
    Node *next;
  };
  Node **table_;

  void resize(int new_size) {
    auto *new_table = new Node*[new_size]();
    for (int i = 0; i < size_; i++) {
      auto *node = table_[i];
      while (node) {
        auto *temp = node;
        node = node->next;
        int index = hash(temp->key) % new_size;
        temp->next = new_table[index];
        new_table[index] = temp;
      }
    }
    delete[] table_;
    table_ = new_table;
    size_ = new_size;
  }

  int hash(K key) {
    // TODO: Implement a hash function for key of type K
    return 0;
  }
};


