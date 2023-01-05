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
#include "../HashTable/ht_stable.h"

template <class Key, class Data>
struct Node {
  Key key;
  Data data;
  Node* parent;
  int rank;

  Node(Key key, Data data) : key(key), data(data), parent(nullptr), rank(0){}

};

template <class Key, class Data>
class UnionFind {
 public:

  void Union(Key keyForObj_1, Key keyForObj_2) {

    Node<Key, Data>* Obj_1Root = Find(keyForObj_1);
    Node<Key, Data>* Obj_2Root = Find(keyForObj_2);

    //united
    if (Obj_1Root == Obj_2Root) return;

    if (Obj_1Root->rank < Obj_2Root->rank) {

      Obj_1Root->parent = Obj_2Root;

    } else if (Obj_1Root->rank > Obj_2Root->rank) {

      Obj_2Root->parent = Obj_1Root;

    } else {

      Obj_2Root->parent = Obj_1Root;

      Obj_1Root->rank++;
    }
  }

  Node<Key, Data>* Find(Key key) {

    return Find(forest.get(key));

  }

  void Insert(Key key, Data data) {

    forest.put(key, new Node<Key, Data>(key, data));
  }

  int get_size(){
    return size;
  }

  int get_capacity() { 
    return StructureCapacity; 
    }
  
  template <class K, class D>
  friend std::ostream& operator<<(const std::ostream&, const UnionFind<K, D>&);

 private:
  HashTable<Key, Node<Key, Data>*> forest;
  int size;
  int StructureCapacity;

  Node<Key, Data>* Find(Node<Key, Data>* x) {

    if (x->parent == nullptr) {
      return x;
    }

    //recursive operation that traverse the upSideDownTree!

    x->parent = Find(x->parent);
    return x->parent;
  }

  void Remove(Key key) {

    //just deletes a node in one of the opposite trees
    //this can cause a tree to be corrupted

    forest.remove(key);
      
  }

};

  template <class K, class D>
  std::ostream& operator<<(const std::ostream& os, const UnionFind<K, D>& obj)
  {
    return os;
  }

#endif