#include "ht_test.h"

int main() {

  HashTable<int, int> ht;

  int prev_size;

    std::cout << " size is :" << ht.Table_size() << std::endl;

  for(int i =0; i < 10000; i++)
  {
    ht.put(i, i);
    if(prev_size != ht.Table_size()){
    std::cout << " size is :" << ht.Table_size() << std::endl;
    prev_size = ht.Table_size();
    }
  }
    std::cout << std::endl;
        ht.Table_Diagram();
    std::cout << std::endl;

  for(int i = 0; i < ht.size(); i++)
  {
    std::cout << ht.get(i) << " ";
  }
    std::cout << std::endl;
        ht.Table_Diagram();
    std::cout << std::endl;

  for(int i = 24; i < 10000; i++)
  {
    ht.remove(i);
    if(prev_size != ht.Table_size()){
    std::cout << " size is :" << ht.Table_size() << std::endl;
    prev_size = ht.Table_size();
    }
  }

    std::cout << std::endl;
        ht.Table_Diagram();
    std::cout << std::endl;

    for(int i = 0; i < 10000; i++)
  {
    std::cout << ht.get(i) << " ";
  }
    std::cout << std::endl;
        ht.Table_Diagram();
    std::cout << std::endl;

    for(int i =0; i < 10000; i++)
  {
    ht.put(i, i);
    if(prev_size != ht.Table_size()){
    std::cout << " size is :" << ht.Table_size() << std::endl;
    prev_size = ht.Table_size();
    }
  }
    std::cout << std::endl;
        ht.Table_Diagram();
    std::cout << std::endl;

    for(int i = 0; i < ht.size(); i++)
  {
    std::cout << ht.get(i) << " ";
  }
    std::cout << " size is :" << ht.Table_size() << std::endl;

    ht.Table_Diagram();
  return 0;
}
