#include "uf_test.h"


// --------------------------DO NOT FORGET TO MODIFY THE CODE THAT THEY WON'T KNOW!-------------------------//

//---------------------- hash table -----------------------------//

int main() {

  HashTable<std::string, int> ht;
  ht.put("hello", 1);
  ht.put("world", 2);
  std::cout << ht.get("hello") << std::endl;
  std::cout << ht.get("world") << std::endl;
  ht.remove("hello");
  std::cout << ht.contains("hello") << std::endl;
  std::cout << ht.contains("world") << std::endl;
  std::cout << ht.size() << std::endl;
  return 0;
}


int main() {
  UnionFind<int, std::string> uf(10);
  Node<int, std::string>* node0 = uf.Insert(0, "node 0");
  Node<int, std::string>* node1 = uf.Insert(1, "node 1");
  Node<int, std::string>* node2 = uf.Insert(2, "node 2");
  Node<int, std::string>* node3 = uf.Insert(3, "node 3");
  uf.Union(node0, node1);
  uf.Union(node2, node3);
  uf.Union(node0, node3);

  std::cout << uf.Find(0)->key << std::endl;
  std::cout << uf.Find(1)->key << std::endl;
  std::cout << uf.Find(2)->key << std::endl;
  std::cout << uf.Find(3)->key << std::endl;

  uf.Remove(node1);

  std::cout << uf.Find(0)->key << std::endl;
  std::cout << uf.Find(1)->key << std::endl;
  std::cout << uf.Find(2)->key << std::endl;
  std::cout << uf.Find(3)->key << std::endl;

  return 0;
}