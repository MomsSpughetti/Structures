/*
Hash table

supports size changing!

Key typname should have operator*(const &size_t, Key& obj)!
*/

#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include "../prime/prime.h"

template <typename Key, typename Data>
class HashTable {
 public:
  HashTable(int size = 17) : size_(size), table_(new Node*[size]()){}

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

  void put(Key key, Data data) {
    int index = hash(key, size_);
    auto *node = table_[index];
    while (node) {
      if (node->key == key) {
        node->data = data;
        return;
      }
      node = node->next;
    }
    node = new Node{key, data};
    node->next = table_[index];
    table_[index] = node;
    if (++count_ > size_) {
      int new_size = closer_prime(size_ * 2);
      resize(new_size);
    }
  }

  Data get(Key key) {
    int index = hash(key, size_);
    std::cout << "the object with id :" << key << "is placed in bucket number:" << index << std::endl;
    auto *node = table_[index];
    while (node) {
      if (node->key == key) {
        return node->data;
      }
      node = node->next;
    }
    return Data{};
  }

  void remove(Key key) {
    int index = hash(key, size_);
    auto *node = table_[index];
    if (node && node->key == key) {
      table_[index] = node->next;
      delete node;
      if (--count_ < size_ / 4) {
        int new_size = size_ / 2;
        if(!is_prime(new_size))
          new_size = closer_prime(new_size);
        resize(new_size);
      }
      return;
    }
    while (node) {
      if (node->next && node->next->key == key) {
        auto *temp = node->next;
        node->next = temp->next;
        delete temp;
        if (--count_ < size_ / 4) {
          int new_size = closer_prime(size_ / 2);
          resize(new_size);
        }
        return;
      }
      node = node->next;
    }
  }

  bool contains(Key key) {
    int index = hash(key, size_);
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

  int Table_size()
  {
    return size_;
  }


  void Table_Diagram()
  {
    for (int i = 0; i < size_; i++)
    {
      std::cout << std::endl << i << " <+> ";
      int c = 0;
      Node* node = table_[i];
      while (node != nullptr)
      {
        c++;
        node = node->next;
      }
      
      std::cout << c << std::endl;

    }
    
  }

 private:
  struct Node {
    Key key;
    Data data;
    Node *next;
  };
  int size_;
  Node **table_;
  int count_ = 0;

  void resize(int new_size) {
    auto *new_table = new Node*[new_size]();
    for (int i = 0; i < size_; i++) {
      auto *node = table_[i];
      while (node) {
        auto *temp = node;
        node = node->next;
        int index = hash(temp->key, new_size) % new_size;
        temp->next = new_table[index];
        new_table[index] = temp;
      }
    }
    delete[] table_;
    table_ = new_table;
    size_ = new_size;
  }

  std::size_t hash(const Key& key, std::size_t table_size) {
    std::size_t multiplier = 2654435761;
    std::size_t shift = 32;
    return static_cast<std::size_t>(static_cast<std::size_t>(multiplier * key) >> shift) % table_size;
  }
};

#endif
