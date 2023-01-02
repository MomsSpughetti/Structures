/*
This implementation adds a StructureCapacity member variable to the UnionFind class, 
which keeps track of the current capacity of the upSideDownTree array. 
The Insert function increases the size of the array by a factor of 2 when 
the key to be inserted is greater than or equal to the current size of the array. 
The Remove function replaces the node to be removed with the last node in the array, 
decrements the size variable, and then checks if the size is less than or equal to half the StructureCapacity. 
If it is, then it decreases the capacity of the upSideDownTree array by a factor of 2.
*/

// --------------------------DO NOT FORGET TO MODIFY THE CODE THAT THEY WON'T KNOW!-------------------------//

#ifndef _UFC_
#define _UFC_

#include <iostream>
#include <ostream>
#include "ht_test.h"

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
  UnionFind(int size = 0) : size(size), upSideDownTree(new Node<Key, Data>[size]) {

    for (int i = 0; i < size; i++) {
      upSideDownTree[i] = Node<Key, Data>{i, Data(), nullptr, 0};
    }

  }

// --------------------------DO NOT FORGET TO MODIFY THE CODE THAT THEY WON'T KNOW!-------------------------//

  ~UnionFind() { 
    delete[] upSideDownTree; 
    }

  Node<Key, Data>* Find(Node<Key, Data>* x) {

    if (x->parent == nullptr) {
      return x;
    }

    //recursive operation that traverse the upSideDownTree!

    x->parent = Find(x->parent);
    return x->parent;
  }

//------------------- modify the rank as you need! ------------ this is a general implementation//

  void Union(Node<Key, Data>* x, Node<Key, Data>* y) {

    Node<Key, Data>* xRoot = Find(x);
    Node<Key, Data>* yRoot = Find(y);

    //united
    if (xRoot == yRoot) return;

    //general implementation! depends on rank!

    if (xRoot->rank < yRoot->rank) {

      xRoot->parent = yRoot;

    } else if (xRoot->rank > yRoot->rank) {

      yRoot->parent = xRoot;

    } else {

      yRoot->parent = xRoot;

      xRoot->rank++;
    }
  }

  Node<Key, Data>* Find(Key key) {

    return Find(&upSideDownTree[key]);

  }

// --------------------------DO NOT FORGET TO MODIFY THE CODE THAT THEY WON'T KNOW!-------------------------//

  Node<Key, Data>* Insert(Key key, Data data) {

    if (key >= size) {

      Node<Key, Data>* old_nodes = upSideDownTree;
      int old_size = size;

      size = std::max(key + 1, size * 2);

      upSideDownTree = new Node<Key, Data>[size];

      for (int i = 0; i < old_size; i++) {
        upSideDownTree[i] = old_nodes[i];
      }

      delete[] old_nodes;
    }

    upSideDownTree[key] = Node<Key, Data>{key, data, nullptr, 0};
  }

    void Remove(Node<Key, Data>* node) {

    node->parent = &upSideDownTree[size - 1];
    node->key = upSideDownTree[size - 1].key;
    node->data = upSideDownTree[size - 1].data;

    size--;

    if (size <= StructureCapacity / 2) {

      Node<Key, Data>* old_nodes = upSideDownTree;
      int old_capacity = StructureCapacity;

      StructureCapacity = StructureCapacity / 2;
      upSideDownTree = new Node<Key, Data>[StructureCapacity];

      for (int i = 0; i < size; i++) {
        upSideDownTree[i] = old_nodes[i];
      }

      delete[] old_nodes;
    }
  }

// --------------------------DO NOT FORGET TO MODIFY THE CODE THAT THEY WON'T KNOW!-------------------------//


  int size(){
    return size;
  }

  int capacity() { 
    return StructureCapacity; 
    }

  friend std::ostream& operator<<(const std::ostream& os, UnionFind){

  }

 private:
  Node<Key, Data>* upSideDownTree;
  int size;
  int StructureCapacity;
};

#endif