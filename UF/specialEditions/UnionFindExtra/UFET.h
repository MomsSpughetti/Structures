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
#include "../../../HashTable/ht_stable.h"

/*
    member extra is an object of kind Extra.
    Extra class should have default constructor!
    Kind Extra sholud have operator+ and operato-!
    the operator action doesn't have to suit his name!
*/
template <class Key, class Data, class Extra>
struct Node {
  Key key;
  Data data;
  Node* parent;
  int rank;
  Extra extra;

  Node(Key key, Data data, Extra extra) : key(key), data(data), parent(nullptr), rank(0), extra(extra){}
};

template <class Key, class Data, class Extra>
class UnionFindExtra {
 public:

 //Obj_1 comes first
  void Union(Key keyForObj_1, Key keyForObj_2) {

    Node<Key, Data, Extra>* Obj_1Root = Find(keyForObj_1);
    Node<Key, Data, Extra>* Obj_2Root = Find(keyForObj_2);

    //at least one key does not exist
    if(!Obj_1Root || !Obj_2Root)
    {
      return;
    }

    //united
    if (Obj_1Root == Obj_2Root) return;

    if (Obj_1Root->rank < Obj_2Root->rank) { //case 1

      Obj_1Root->parent = Obj_2Root;
      //extra_b_new = extra_a_old + extra_b_old
      Obj_2Root->extra = Obj_1Root->extra + Obj_2Root->extra;
      //extra_a_new = extra_a_old - extra_b_new
      Obj_1Root->extra = Obj_1Root->extra - Obj_2Root->extra;

    } else if (Obj_1Root->rank > Obj_2Root->rank) { //case 2

      Obj_2Root->parent = Obj_1Root;
      //extra_b_new = extra_b_old
      //Obj_2Root->extra = Obj_2Root->extra;
      //extra_a_new = extra_a_old
      //Obj_1Root->extra = Obj_1Root->extra

    } else { //case 3

      Obj_2Root->parent = Obj_1Root;

      Obj_1Root->rank++;
    }
  }

  Node<Key, Data, Extra>* Find(Key key) {

    // get pointer to the wanted node
    Node<Key, Data, Extra>** ptrToTargetNode = forest.get(key);
    
    //Key not found
    if(ptrToTargetNode == nullptr)
    {
      return nullptr;
    }
    Node<Key, Data, Extra>* TargetNode = *ptrToTargetNode;

    //update extra before reshaping the tree
    updateExtrasFromNode_x_ToRoot(TargetNode);

    //reshape
    return Find(TargetNode);
  }

  void Insert(Key key, Data data, Extra extra) {

    forest.put(key, new Node<Key, Data, Extra>(key, data, extra));
  }


  template <class K, class D, class E>
  friend std::ostream& operator<<(std::ostream&, const UnionFindExtra<K, D, E>&);

  HashTable<Key, Node<Key, Data, Extra>*> forest;
 private:

  Extra FindSumOfExtrasFromNode_x_ToRoot(Node<Key, Data, Extra>* x) {
    Extra sum;
    Node<Key, Data, Extra>* temp = x; //no need for temp, but looks nicer with it
    while(temp)
    {
        sum = sum + temp->extra;
        temp = temp->parent;
    }
    return sum;
  }

  void updateExtrasFromNode_x_ToRoot(Node<Key, Data, Extra>* x) {

    Extra sumOfExtras = FindSumOfExtrasFromNode_x_ToRoot(x);
    Extra PrevExtra; // Extra() - the empty contructor should set the new object to a neutral value => like 0 for - and +
    Node<Key, Data, Extra>* temp = x;

    //it does not affect the root nor the first son in the series
    while(temp->parent && temp->parent->parent)
    {
        temp->extra = sumOfExtras - PrevExtra;
        sumOfExtras = sumOfExtras - temp->extra;
        PrevExtra = temp->extra;
        temp = temp->parent;

    }
  }

  Node<Key, Data, Extra>* Find(Node<Key, Data, Extra>* x) {

    if (x->parent == nullptr) {
      return x;
    }

    //recursive operation that traverse the upSideDownTree! it also updates the extra for each x
    x->parent = Find(x->parent);

    return x->parent;
  }

  void Remove(Key key) {

    //just deletes a node in one of the opposite trees
    //this can cause a tree to be corrupted

    forest.remove(key);
      
  }


//Errors
};

  template <class D, class E>
  std::ostream& operator<<(std::ostream& os, UnionFindExtra<int, D, E>& obj)
  {
    //obj.forest.Table_Diagram();
    //obj.forest.Table_Diagram();
    HashTable<int, int> parents;

    try
    {
    //works when the keys are from 0 to count_!
    for (int i = 0; i < obj.forest.count_; i++)
    {
      //get the parent of node with key i
      Node<int, D, E>* parent = obj.Find(i);
      
      //get the number of how many childrens do parent have (parent included)
      int* parentDataInParents = parents.get(parent->key);

      if(!parentDataInParents)
      {
        parents.put(parent->key, 1);
        continue;
      }

      //increase children count
      (*parentDataInParents)++;

    }
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    
    for (int i = 0; i < obj.forest.count_; i++)
    {
      int* pp = parents.get(i);
      if(!pp)
      {
        continue;
      }
      std::cout << std::endl;
      std::cout << "[" << i <<", " << *pp << "] ";
    }
    parents.Table_Diagram();
    std::cout << std::endl;
    return os;
  }

#endif