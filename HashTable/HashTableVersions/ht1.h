/*
Hash table

supports size changing!

*/

#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include "../prime/prime.h"

// Templated hash table class that stores key-value pairs
template <typename K, typename Data>
class HashTable {
 public:
  // Constructor that initializes the hash table with a given size
  HashTable(int size = 17) : size_(size), table_(new Node*[size]()){}

  // Destructor that frees the memory used by the hash table
  ~HashTable() {
    for (int i = 0; i < size_; i++) {
      // Delete all nodes in the linked list for each index
      auto *node = table_[i];
      while (node) {
        auto *temp = node;
        node = node->next;
        delete temp;
      }
    }
    delete[] table_;
  }

  // Inserts a key-value pair into the hash table
  void put(Key key, Data data) {
    // Calculate the index for the key
    int index = hash(key, size_);
    auto *node = table_[index];
    // Check if the key already exists in the hash table
    while (node) {
      if (node->key == key) {
        // Update the value for the key if it exists
        node->data = data;
        return;
      }
      node = node->next;
    }
    // Insert a new node into the linked list if the key does not exist
    node = new Node{key, data};
    node->next = table_[index];
    table_[index] = node;
    // Check if the hash table needs to be resized
    if (++count_ > size_) {
      // Increase the size of the hash table if the load factor exceeds 1
      int new_size = closer_prime(size_ * 2);
      resize(new_size);
    }
  }

  // Retrieves the value associated with a given key
  Data get(Key key) {
    // Calculate the index for the key
    int index = hash(key, size_);
    auto *node = table_[index];
    // Search for the key in the linked list
    while (node) {
      if (node->key == key) {
        // Return the value if the key is found
        return node->data;
      }
      node = node->next;
    }
    // Return an empty data object if the key is not found
    return Data{};
  }

  // Removes a key-value pair from the hash table
  void remove(Key key) {
    // Calculate the index for the key
    int index = hash(key, size_);
    auto *node = table_[index];
    if (node && node->key == key) {
      // Remove the head node of the linked list if it has the key
      table_[index] = node->next;
      delete node;
      // Check if the hash table needs to be resized
      if (--count_ < size_ / 4) {
        // Decrease the size of the hash table if the load factor falls below 0.25
        int new_size = size_ / 2;
        if(!is_prime(new_size))
          new_size = closer_prime(new_size);
        resize(new_size);
      }
      return;
    }
    // Search for the key in the linked list
    while (node) {
      if (node->next && node->next->key == key) {
        // Remove the node if it has the key
        auto *temp = node->next;
        node->next = temp->next;
        delete temp;
        // Check if the hash table needs to be resized
        if (--count_ < size_ / 4) {
          // Decrease the size of the hash table if the load factor falls below 0.25
          int new_size = closer_prime(size_ / 2);
          resize(new_size);
        }
        return;
      }
      node = node->next;
    }
  }

  // Returns true if the hash table contains a given key
  bool contains(Key key) {
    // Calculate the index for the key
    int index = hash(key, size_);
    auto *node = table_[index];
    // Search for the key in the linked list
    while (node) {
      if (node->key == key) {
        // Return true if the key is found
        return true;
      }
      node = node->next;
    }
    // Return false if the key is not found
    return false;
  }

  // Returns the number of key-value pairs in the hash table
  int size() {
    return count_;
  }

 private:
  // Inner class that represents a node in a linked list
  struct Node {
    Key key;
    Data data;
    Node *next;
  };
  // Array of pointers to linked list nodes
  Node **table_;
  // Size of the hash table
  int size_;
  // Number of key-value pairs in the hash table
  int count_ = 0;

  // Resizes the hash table to a new size
  void resize(int new_size) {
    // Create a new array of pointers to linked list nodes
    auto *new_table = new Node*[new_size]();
    for (int i = 0; i < size_; i++) {
      // Rehash all nodes in the old table and insert them into the new table
      auto *node = table_[i];
      while (node) {
        auto *temp = node;
        node = node->next;
        // Calculate the new index for the node
        int index = hash(temp->key, new_size) % new_size;
        // Insert the node into the new table
        temp->next = new_table[index];
        new_table[index] = temp;
      }
    }
    // Delete the old table and update the table pointer
    delete[] table_;
    table_ = new_table;
    // Update the size of the hash table
    size_ = new_size;
  }

  // Hashes a key to a table index
  constexpr std::size_t hash(const Key& key, std::size_t table_size) {
    // Hash function constants
    constexpr std::size_t multiplier = 2654435761;
    constexpr std::size_t shift = 32;
    // Hash the key and return the modulo of the result and the table size
    return ((multiplier * key) >> shift) % table_size;
  }
};

#endif
