#ifndef _OUR_TREE
#define _OUR_TREE


/*
first version of an AVL tree
supports basic functions
*/

#include <iostream>

//helper functions
int max(int a, int b)
{
    return (a < b)? b : a;
}

// Node class template
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

};

// AVL tree class template
template <typename Key, typename Data>
class RankedAVLTree {
 public:
 RankedAVLTree() : root(nullptr) {}

  ~RankedAVLTree() {
    DeleteTree(root);
  }

  // Insert a new key-value pair into the tree
  void Insert(const Key &key, const Data &data) {
    root = Insert(root, key, data);
  }

  // Remove a key and its associated value from the tree
  void Remove(const Key &key) {
    root = Remove(root, key);
  }

  // Find the value associated with a given key
  Data* Find(const Key &key) {
    return Find(root, key);
  }

// Find the rank of a given key (i.e. the number of nodes with a smaller key)
int GetRank(const Key &key) {
  return GetRank(root, key);
}

// Find the kth smallest node in the tree (0-indexed)
Node<Key, Data>* FindByRank(int k) {
  return FindByRank(root, k);
}

  //print the nodes in order
  void printInOrder()
  {
    std::cout << std::endl;
    printInOrder_aux(this->root);
    std::cout << std::endl;
  }

  //do not forget to free the returned array
  Node<Key, Data>** TreeNodesToArray()
  {
    Node<Key, Data>** array = new Node<Key, Data>*[this->root->size];
    int place = 0;
    TreeNodesToArray(this->root, array, place);
    return array;
  }

  int get_size() const{
    return root->size;
  }

 private:
  Node<Key, Data> *root;

  // Recursive helper function to insert a new key-value pair into the tree
// Recursive helper function to insert a new key-value pair into the tree
    Node<Key, Data>* Insert(Node<Key, Data> *node, const Key &key, const Data &data) {
        if (!node) {
            return new Node<Key, Data>(key, data);
        }
        if (key < node->key) {
            node->left = Insert(node->left, key, data);
        } else if (key > node->key) {
            node->right = Insert(node->right, key, data);
        } else {
            // Key already exists, update the value
            //node->data = data;
            return nullptr;
        }
        // Update the size of the node
        node->size = 1 + GetSize(node->left) + GetSize(node->right);
        // Update the height of the node
        node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
        // Balance the tree
        return Balance(node);
        }
  
// Recursive helper function to remove a key and its associated value from the tree
Node<Key, Data>* Remove(Node<Key, Data> *node, const Key &key) {
  if (!node) {
    return nullptr;
  }
  if (key < node->key) {
    node->left = Remove(node->left, key);
  } else if (key > node->key) {
    node->right = Remove(node->right, key);
  } else {
    // Key found
    if (!node->left || !node->right) {
      // Node has at most one child
      Node<Key, Data> *temp = node->left ? node->left : node->right;
      if (!temp) {
        // Node has no children
        delete node;
        return nullptr;
      }
      // Node has one child
      *node = *temp;
      delete temp;
    } else {
      // Node has two children
      // Find the inorder successor (smallest in the right subtree)
      Node<Key, Data> *temp = FindMin(node->right);
      // Copy the inorder successor's content to this node
      node->key = temp->key;
      node->data = temp->data;
      // Delete the inorder successor
      node->right = Remove(node->right, temp->key);
    }
  }
  // Update the size of the node
  node->size = 1 + GetSize(node->left) + GetSize(node->right);
  // Update the height of the node
  node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
  // Balance the tree
  return Balance(node);
}

// Find the value associated with a given key
Data* Find(Node<Key, Data> *node, const Key &key) {
  if (!node) {
    return nullptr;
  }
  if (key == node->key) {
    return &node->data;
  } else if (key < node->key) {
    return Find(node->left, key);
  } else {
    return Find(node->right, key);
  }
}

// Recursive helper function to find the kth smallest node in the tree (0-indexed)
Node<Key, Data>* FindByRank(Node<Key, Data> *node, int k) {
  if (!node) {
    return nullptr;
  }
  int leftSize = GetSize(node->left);
  if (k < leftSize) {
    // kth smallest node is in the left subtree
    return FindByRank(node->left, k);
  } else if (k > leftSize) {
    // kth smallest node is in the right subtree
    return FindByRank(node->right, k - leftSize - 1);
  } else {
    // kth smallest node is this node
    return node;
  }
}

// Get the number of nodes in the subtree rooted at a given node
int GetSize(Node<Key, Data> *node) {
  return node ? node->size : 0;
}

// Recursive helper function to find the rank of a given key (i.e. the number of nodes with a smaller key)
int GetRank(Node<Key, Data> *node, const Key &key) {
  if (!node) {
    return 0;
  }
  if (key < node->key) {
    // Key is in the left subtree
    return GetRank(node->left, key);
  } else if (key > node->key) {
    // Key is in the right subtree
    return 1 + GetSize(node->left) + GetRank(node->right, key);
  } else {
    // Key is this node
    return GetSize(node->left);
  }
}

// Find the node with the minimum key in the tree
Node<Key, Data>* FindMin(Node<Key, Data> *node) {
  if (!node->left) {
    return node;
  }
  return FindMin(node->left);
}

// Get the height of a node
int GetHeight(Node<Key, Data> *node) {
  return node ? node->height : 0;
}

// Get the balance factor of a node
int GetBalanceFactor(Node<Key, Data> *node) {
  return GetHeight(node->right) - GetHeight(node->left);
}

// Balance the tree
Node<Key, Data>* Balance(Node<Key, Data> *node) {
  // Update the height of the node
  node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
  node->size = 1 + GetSize(node->left) + GetSize(node->right);

  // Get the balance factor
  int balance_factor = GetBalanceFactor(node);
  // Left left case
  if (balance_factor > 1 && GetBalanceFactor(node->right) >= 0) {
    return RotateLeft(node);
  }
  // Right right case
  if (balance_factor < -1 && GetBalanceFactor(node->left) <= 0) {
    return RotateRight(node);
  }
  // Left right case
  if (balance_factor > 1 && GetBalanceFactor(node->right) < 0) {
    node->right = RotateRight(node->right);
    return RotateLeft(node);
  }
  // Right left case
  if (balance_factor < -1 && GetBalanceFactor(node->left) > 0) {
    node->left = RotateLeft(node->left);
    return RotateRight(node);
  }
  return node;
}

// Perform left rotation
Node<Key, Data> *RotateLeft(Node<Key, Data> *node) {
  Node<Key, Data> *temp = node->right;
  node->right = temp->left;
  temp->left = node;
  // Update the height of the nodes
  node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
  temp->height = 1 + max(GetHeight(temp->left), GetHeight(temp->right));
  node->size = 1 + GetSize(node->left) + GetSize(node->right);
  temp->size = 1 + GetSize(temp->left) + GetSize(temp->right);

  return temp;
}

// Perform right rotation
Node<Key, Data>* RotateRight(Node<Key, Data> *node) {
  Node<Key, Data> *temp = node->left;
  node->left = temp->right;
  temp->right = node;
  // Update the height of the nodes
  node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
  temp->height = 1 + max(GetHeight(temp->left), GetHeight(temp->right));
  node->size = 1 + GetSize(node->left) + GetSize(node->right);
  temp->size = 1 + GetSize(temp->left) + GetSize(temp->right);

  return temp;
}

// Delete the tree
void DeleteTree(Node<Key, Data> *node) {
  if (!node) {
    return;
  }
  DeleteTree(node->left);
  DeleteTree(node->right);
  delete node;
}

//prints the nodes in order

void printInOrder_aux(Node<Key, Data>* router)
{
  // dead end
  if(router == nullptr)
  {
    return;
  }
  
  // printing order: left -> parent -> right
  printInOrder_aux(router->left);
  std::cout << "[ " << router->key << ", " << router->data << "] ";
  printInOrder_aux(router->right);

}

  void TreeNodesToArray(Node<Key, Data>* root, Node<Key, Data>** arr, int &i)
  {
    if(!root)
    {
      return;
    }

    TreeNodesToArray(root->left, arr, i);
    arr[i] = root;
    i++;
    TreeNodesToArray(root->right, arr, i);
  }


};


#endif

