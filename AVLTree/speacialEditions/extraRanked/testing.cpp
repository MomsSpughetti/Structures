#include "RankedAvlTreeExtra.h"
#include <string.h>

int main() {
  // Create an AVL tree with integer keys and string values
  RankedAVLTreeExtra<int, std::string, int> tree;
  // Insert some key-value pairs

  tree.printInOrder();


  for (int i = 1; i < 11; i++)
  {
    tree.Insert(i, "1");
  }
  
  tree.printInOrder();

  tree.updateRange(10, 1);
  tree.printInOrder();

  for (int i = 1; i < 21; i++)
  {
    tree.Insert(i, "2");
  }
  tree.printInOrder();

  tree.updateRange(20, 2);
  tree.updateRange(10, -2);
  tree.printInOrder();

  for (int i = 1; i < 31; i++)
  {
    tree.Insert(i, "3");
  }
  tree.printInOrder();

  tree.updateRange(30, 3);
  tree.updateRange(20, -3);
  tree.printInOrder();

  for (int i = 1; i < 41; i++)
  {
    tree.Insert(i, "4");
  }
  tree.printInOrder();

  tree.updateRange(40, 4);
  tree.updateRange(30, -4);
  tree.printInOrder();

  for (int i = 1; i < 51; i++)
  {
    tree.Insert(i, "5");
  }
  for (int i = 11; i < 21; i+=1)
  {

    if(i==19){
      std::cout << "";
    }

    if(tree.getValidExtra(21)!=3){
      std::cout << "";
    }
    tree.Remove(i);
  }
  tree.printInOrder();

  tree.updateRange(50, 5);
  tree.updateRange(40, -5);
  tree.printInOrder();

  tree.printInOrder();

  return 0;
  }
  