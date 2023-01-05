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
template <class Key, class Data>
class Node {
 public:
  Key key;
  Data data;
  int height;
  Node<Key, Data> *left;
  Node<Key, Data> *right;

  explicit Node(const Key &key, const Data &data)
      : key(key), data(data), height(1), left(nullptr), right(nullptr) {}
};

// AVL tree class template
template <class Key, class Data>
class AVLTree {
 public:
  AVLTree() : root(nullptr) {}

  ~AVLTree() {
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

  //print the nodes in order
  void printInOrder()
  {
    std::cout << std::endl;
    printInOrder_aux(this->root);
    std::cout << std::endl;
  }

  void PrintTree()
  {
    PrintTree(root, 0);
  }

 private:
  Node<Key, Data> *root;

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
      node->data = data;
      return node;
    }
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

// Helper function to print the tree using ASCII art
void PrintTree(Node<Key, Data> *node, int level) {
  if (!node) {
    return;
  }
  PrintTree(node->right, level + 2);
  std::cout << std::string(level, ' ') << node->key << std::endl;
  PrintTree(node->left, level + 2);
  }
};

#endif