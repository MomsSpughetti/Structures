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
  tree.printInOrder();
  for (int i = 1; i < 100; i+=1)
  {
    tree.Remove(i);
    tree.Insert(i, "changed");
  }
  tree.printInOrder();
  for (int i = 16; i < 100; i+=1)
  {
    tree.Remove(i);
  }

  std::string newData = "Changed";
  int ip = 14;

  //tree.update(ip,ip, newData);
  //tree.Remove(14);
  tree.printInOrder();
  for (int i = 0; i < 13; i++)
  {
    if(i == 10 || i == 11 || i == 12)
      std::cout << "";
    //tree.update(i, i, newData);
  }
  
  for (int i = 1; i < 100; i++)
  {
    tree.Insert(i, "number");
  }
  
  tree.printInOrder();

  return 0;
  }