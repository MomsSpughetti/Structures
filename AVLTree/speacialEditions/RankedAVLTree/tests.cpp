#include <iostream>
#include <stdlib.h>
#include "RankedTree.h"

#include <cassert>

#include <cassert>
#include <iostream>

int main() {
  AVLTree<int, std::string> tree;

  // Test the insert function
  tree.Insert(5, "apple");
  tree.Insert(3, "banana");
  tree.Insert(7, "cherry");
  tree.Insert(2, "date");
  tree.Insert(4, "elderberry");
  tree.Insert(6, "fig");
  tree.Insert(8, "grape");

  std::cout << "In-order traversal: ";
  tree.printInOrder();
  std::cout << std::endl;

  // Test the find function
  assert(*tree.Find(5) == "apple");
  assert(*tree.Find(6) == "fig");
  assert(*tree.Find(7) == "cherry");
  assert(*tree.Find(8) == "grape");
  assert(tree.Find(9) == nullptr);

  // Test the rank and find by rank functions
  assert(tree.GetRank(5) == 2);
  assert(tree.GetRank(6) == 3);
  assert(tree.GetRank(7) == 4);
  assert(tree.GetRank(8) == 5);
  assert(tree.GetRank(9) == 6);
  assert(tree.FindByRank(0)->data == "date");
  assert(tree.FindByRank(3)->data == "elderberry");
  assert(tree.FindByRank(5)->data == "grape");

  std::cout << "Find by rank (0): " << tree.FindByRank(0)->data << std::endl;
  std::cout << "Find by rank (3): " << tree.FindByRank(3)->data << std::endl;
  std::cout << "Find by rank (5): " << tree.FindByRank(5)->data << std::endl;
  std::cout << "Find by rank (6): " << tree.FindByRank(6)->data << std::endl;
  std::cout << std::endl;

  // Test the remove function
  tree.Remove(5);
  tree.Remove(7);
  assert(tree.Find(5) == nullptr);
  assert(tree.Find(7) == nullptr);

  std::cout << "In-order traversal: ";
  tree.printInOrder();
  std::cout << std::endl;

  // Test the find by rank function again
  assert(tree.FindByRank(0)->data == "date");
  assert(tree.FindByRank(3)->data == "fig");
  assert(tree.FindByRank(6) == nullptr);

  std::cout << "Find by rank (0): " << tree.FindByRank(0)->data << std::endl;
  std::cout << "Find by rank (3): " << tree.FindByRank(3)->data << std::endl;
  std::cout << "Find by rank (5): " << tree.FindByRank(5) << std::endl;
  std::cout << "Find by rank (6): " << tree.FindByRank(6) << std::endl;
  std::cout << std::endl;

  // Test the insert function again
  tree.Insert(5, "apple");
  tree.Insert(7, "cherry");
  assert(*tree.Find(5) == "apple");
  assert(*tree.Find(7) == "cherry");

  std::cout << "In-order traversal: ";
  tree.printInOrder();
  std::cout << std::endl;

  // Test the rank and find by rank functions again
  assert(tree.GetRank(5) == 3);
  assert(tree.GetRank(6) == 4);
  assert(tree.GetRank(7) == 5);
  assert(tree.GetRank(8) == 6);
  assert(tree.GetRank(9) == 7);
  assert(tree.FindByRank(0)->data == "date");
  assert(tree.FindByRank(3)->data == "fig");
  assert(tree.FindByRank(5)->data == "cherry");
  assert(tree.FindByRank(6)->data == "grape");
  assert(tree.FindByRank(7) == nullptr);

  // Test the remove function again
  tree.Remove(2);
  tree.Remove(4);
  tree.Remove(6);
  tree.Remove(8);
  assert(tree.Find(2) == nullptr);
  assert(tree.Find(4) == nullptr);
  assert(tree.Find(6) == nullptr);
  assert(tree.Find(8) == nullptr);
  
  std::cout << std::endl;
  std::cout << "In-order traversal: ";
  tree.printInOrder();
  std::cout << std::endl;

  // Test the find by rank function one more time
  assert(tree.FindByRank(0)->data == "apple");
  assert(tree.FindByRank(1)->data == "banana");
  assert(tree.FindByRank(2)->data == "cherry");
  assert(tree.FindByRank(3) == nullptr);

  std::cout << "Find by rank (0): " << tree.FindByRank(0)->data << std::endl;
  std::cout << "Find by rank (1): " << tree.FindByRank(1)->data << std::endl;
  std::cout << "Find by rank (2): " << tree.FindByRank(2)->data << std::endl;
  std::cout << "Find by rank (3): " << tree.FindByRank(3) << std::endl;
  std::cout << std::endl;
  std::cout << "In-order traversal: ";
  tree.printInOrder();
  std::cout << std::endl;

  return 0;
}