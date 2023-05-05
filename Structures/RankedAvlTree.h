#ifndef _OUR_TREE
#define _OUR_TREE


/*
first version of an AVL tree
supports basic functions
key should have:
  operators:
    - <
    - >
    - ==
*/

#include <iostream>
#include <stdlib.h>
#include <math.h>

template <typename Key, typename Data>
class Node {
 public:
  Key key;
  Data data;
  int height;
  Node<Key, Data> *left;
  Node<Key, Data> *right;
  int size;

  explicit Node(const Key &key, const Data &data)
      : key(key), data(data), height(1), left(nullptr), right(nullptr), size(1) {}

  ~Node() = default;

};

template <typename Key, typename Data>
class RankedAVLTree {
 public:
 RankedAVLTree() : root(nullptr) {}

  ~RankedAVLTree() {
    DeleteTree(root);
  }

  void Insert(const Key &key, const Data &data) {
    root = Insert(root, key, data);
  }

  void Remove(const Key &key) {
    root = Remove(root, key);
  }

  void update(Key& prevKey, Key& newkey, Data& newData)
  {
    Node<Key, Data>* temp = FindNode(root, prevKey);

    if(!temp) {return;} 

    if(!(temp->key == prevKey)) {return;}

    this->Remove(prevKey);

    this->Insert(newkey, newData);
  }
  
  Data* Find(const Key &key) {
    return Find(root, key);
  }

int GetRank(const Key &key) {
  return GetRank(root, key);
}

Node<Key, Data>* FindByRank(int k) {
  return FindByRank(root, k);
}

  void printInOrder()
  {
    std::cout << std::endl;
    printInOrder_aux(this->root);
    std::cout << std::endl;
  }

  Node<Key, Data>** TreeNodesToArray()
  {
    if(!this->root)
    return nullptr;
    Node<Key, Data>** array = new Node<Key, Data>*[this->root->size];
    int place = 0;
    TreeNodesToArray(this->root, array, place);
    return array;
  }

  int get_size() const{
    return root->size;
  }

  Key& getIdByReference(const Key& key)
  {
    return FindNode(root, key)->key;
  }

 private:
  Node<Key, Data> *root;

    Node<Key, Data>* Insert(Node<Key, Data> *no, const Key &key, const Data &data) {
        if (!no) {
            return new Node<Key, Data>(key, data);
        }
        if (key < no->key) 
        {
          no->left = Insert(no->left, key, data);
        } else if (key > no->key) 
        {
            no->right = Insert(no->right, key, data);
        } else 
        {
            return nullptr;
        }
        no->size = 1 + GetSize(no->left) + GetSize(no->right);
        no->height = 1 + std::max(GetHeight(no->left), GetHeight(no->right));
        return Balance(no);
        }
  
Node<Key, Data>* Remove(Node<Key, Data> *no, const Key &key) {
  if (!no) {
    return nullptr;
  }
  if (key > no->key) 
  {
    no->right = Remove(no->right, key);
  } else if (key < no->key) 
  {
    no->left = Remove(no->left, key);
  } else 
  {
    if (!no->left || !no->right) 
    {
      Node<Key, Data> *temp = no->left ? no->left : no->right;
      if (!temp) 
      {
        delete no;
        return nullptr;
      }
      *no = *temp;
      delete temp;
    } else 
    {
      Node<Key, Data> *temp = FindMin(no->right);
      no->key = temp->key;
      no->data = temp->data;
      no->right = Remove(no->right, temp->key);
    }
  }
  no->size = 1 + GetSize(no->left) + GetSize(no->right);
  no->height = 1 + std::max(GetHeight(no->left), GetHeight(no->right));
  return Balance(no);
}

Data* Find(Node<Key, Data> *node, const Key &key) {
  if (!node) {
    return nullptr;
  }
  if (key == node->key) 
  {
    return &node->data;
  } else if (key < node->key) 
  {
    return Find(node->left, key);

  } else 
  {

    return Find(node->right, key);
  }
}

Node<Key, Data>* FindNode(Node<Key, Data> *no, const Key &key) {
  if (!no) {
    return nullptr;
  }
  if (key == no->key) 
  {
    return no;
  } else if (key < no->key) 
  {
    return FindNode(no->left, key);
  } else 
  {
    return FindNode(no->right, key);
  }
}
Node<Key, Data>* FindByRank(Node<Key, Data> *no, int k) {
  if (!no) {
    return nullptr;
  }
  int leftSize = GetSize(no->left);
  if (k < leftSize) {
    return FindByRank(no->left, k);
  } else if (k > leftSize) {
    return FindByRank(no->right, k - leftSize - 1);
  } else {
    return no;
  }
}

int GetSize(Node<Key, Data> *node) {
  return node ? node->size : 0;
}

int GetRank(Node<Key, Data> *no, const Key &key) {
  if (!no) {
    return 0;
  }
  if (key < no->key) {
    return GetRank(no->left, key);
  } else if (key > no->key) {
    return 1 + GetSize(no->left) + GetRank(no->right, key);
  } else {
    return GetSize(no->left);
  }
}

Node<Key, Data>* FindMin(Node<Key, Data> *node) {
  if (!node->left) {
    return node;
  }
  return FindMin(node->left);
}

int GetHeight(Node<Key, Data> *node) {
  return node ? node->height : 0;
}

int GetBalanceFactor(Node<Key, Data> *node) {
  return GetHeight(node->right) - GetHeight(node->left);
}

Node<Key, Data>* Balance(Node<Key, Data> *node) {
  node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
  node->size = 1 + GetSize(node->left) + GetSize(node->right);

  int balance_factor = GetBalanceFactor(node);
  if (balance_factor < -1 && GetBalanceFactor(node->left) <= 0) {
    return RotateRight(node);
  }
  if (balance_factor > 1 && GetBalanceFactor(node->right) >= 0) {
    return RotateLeft(node);
  }
  if (balance_factor < -1 && GetBalanceFactor(node->left) > 0) {
    node->left = RotateLeft(node->left);
    return RotateRight(node);
  }
  if (balance_factor > 1 && GetBalanceFactor(node->right) < 0) {
    node->right = RotateRight(node->right);
    return RotateLeft(node);
  }
  return node;
}

Node<Key, Data> *RotateLeft(Node<Key, Data> *node) {
  Node<Key, Data> *temp = node->right;
  node->right = temp->left;
  temp->left = node;
  node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
  temp->height = 1 + std::max(GetHeight(temp->left), GetHeight(temp->right));
  node->size = 1 + GetSize(node->left) + GetSize(node->right);
  temp->size = 1 + GetSize(temp->left) + GetSize(temp->right);

  return temp;
}

Node<Key, Data>* RotateRight(Node<Key, Data> *node) {
  Node<Key, Data> *temp = node->left;
  node->left = temp->right;
  temp->right = node;
  node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
  temp->height = 1 + std::max(GetHeight(temp->left), GetHeight(temp->right));
  node->size = 1 + GetSize(node->left) + GetSize(node->right);
  temp->size = 1 + GetSize(temp->left) + GetSize(temp->right);

  return temp;
}

void DeleteTree(Node<Key, Data> *node) {
  if (!node) {
    return;
  }
  DeleteTree(node->left);
  DeleteTree(node->right);
  delete node;
}


void printInOrder_aux(Node<Key, Data>* router)
{
  if(router == nullptr)
  {
    return;
  }
  
  printInOrder_aux(router->left);
  std::cout << "[ " << router->key << ", " << router->data << "] ";
  printInOrder_aux(router->right);

}

  void TreeNodesToArray(Node<Key, Data>* node, Node<Key, Data>** arr, int &i)
  {
    if(!node)
    {
      return;
    }

    TreeNodesToArray(node->left, arr, i);
    arr[i] = node;
    i++;
    TreeNodesToArray(node->right, arr, i);
  }


};


#endif

