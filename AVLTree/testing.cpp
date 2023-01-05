#include "tested_AVLTree.h"
#include <string.h>

int main() {
  // Create an AVL tree with integer keys and string values
  AVLTree<int, std::string> tree;
  // Insert some key-value pairs
  tree.Insert(5, "Five");
  tree.Insert(3, "Three");
  tree.Insert(2, "Two");
  tree.Insert(4, "Four");
  tree.Insert(7, "Seven");
  tree.Insert(6, "Six");
  tree.Insert(1, "One");
  tree.Insert(0, "Zero");
  tree.Insert(-1, "MOne");
  tree.Insert(-2, "MOne");
  tree.Insert(-3, "MOne");

  tree.Insert(5, "Five");
  
  tree.PrintTree();

  // Find the value associated with the key 4
  std::string *value = tree.Find(4);
  if (value) {
    std::cout << *value << std::endl; // Outputs "Four"
  }
  // Remove the key-value pair with key 5
  tree.Remove(5);
  // Try to find the value associated with the key 5
  value = tree.Find(5);
  if (!value) {
    std::cout << "Key not found" << std::endl; // Outputs "Key not found"

  tree.printInOrder();
  tree.PrintTree();
  }
  return 0;
}