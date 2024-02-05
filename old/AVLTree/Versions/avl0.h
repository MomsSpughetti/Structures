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
template <typename K, typename D>
class Node {
 public:
  K key;
  D data;
  int height;
  Node<K, D> *left;
  Node<K, D> *right;

  explicit Node(const K &key, const D &data)
      : key(key), data(data), height(1), left(nullptr), right(nullptr) {}
};

// AVL tree class template
template <typename K, typename D>
class AVLTree {
 public:
  AVLTree() : root_(nullptr) {}

  ~AVLTree() {
    DeleteTree(root_);
  }

  // Insert a new key-value pair into the tree
  void Insert(const K &key, const D &data) {
    root_ = Insert(root_, key, data);
  }

  // Remove a key and its associated value from the tree
  void Remove(const K &key) {
    root_ = Remove(root_, key);
  }

  // Find the value associated with a given key
  D* Find(const K &key) {
    return Find(root_, key);
  }

 private:
  Node<K, D> *root_;

  // Recursive helper function to insert a new key-value pair into the tree
  Node<K, D>* Insert(Node<K, D> *node, const K &key, const D &data) {
    if (!node) {
      return new Node<K, D>(key, data);
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
  Node<K, D>* Remove(Node<K, D> *node, const K &key) {
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
        Node<K, D> *temp = node->left ? node->left : node->right;
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
      Node<K, D> *temp = FindMin(node->right);
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
D* Find(Node<K, D> *node, const K &key) {
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
Node<K, D>* FindMin(Node<K, D> *node) {
  if (!node->left) {
    return node;
  }
  return FindMin(node->left);
}

// Get the height of a node
int GetHeight(Node<K, D> *node) {
  return node ? node->height : 0;
}

// Get the balance factor of a node
int GetBalanceFactor(Node<K, D> *node) {
  return GetHeight(node->right) - GetHeight(node->left);
}

// Balance the tree
Node<K, D>* Balance(Node<K, D> *node) {
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
Node<K, D> *RotateLeft(Node<K, D> *node) {
  Node<K, D> *temp = node->right;
  node->right = temp->left;
  temp->left = node;
  // Update the height of the nodes
  node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
  temp->height = 1 + max(GetHeight(temp->left), GetHeight(temp->right));
  return temp;
}

// Perform right rotation
Node<K, D>* RotateRight(Node<K, D> *node) {
  Node<K, D> *temp = node->left;
  node->left = temp->right;
  temp->right = node;
  // Update the height of the nodes
  node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
  temp->height = 1 + max(GetHeight(temp->left), GetHeight(temp->right));
  return temp;
}

// Delete the tree
void DeleteTree(Node<K, D> *node) {
  if (!node) {
    return;
  }
  DeleteTree(node->left);
  DeleteTree(node->right);
  delete node;
}
};




#endif