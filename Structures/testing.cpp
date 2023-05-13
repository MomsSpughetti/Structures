#include "RankedAvlTree.h"
#include <string.h>

int main() {
  // Create an AVL tree with integer keys and string values
  RankedAVLTree<int, std::string> tree;
  // Insert some key-value pairs

  // 1 -> 3 -> 5 -> .. -> 101
  for (int i = 1; i < 100; i++)
  {
    tree.Insert(i, "number");
  }
  for (int i = 1; i < 100; i+=1)
  {
    tree.Remove(i);
    tree.Insert(i, "changed");
  }
  for (int i = 16; i < 100; i+=1)
  {
    tree.Remove(i);
  }

  std::string newData = "Changed";
  //int ip = 14;

  
  for (int i = 1; i < 100; i++)
  {
    tree.Insert(i, "number");
  }

  for (int i = 0; i < 100; i++)
  {
    tree.Remove(i);
    tree.Insert(i, newData);
  }
  
  return 0;
  }
  