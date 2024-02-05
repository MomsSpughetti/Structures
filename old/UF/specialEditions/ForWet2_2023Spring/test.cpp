#include "HashTable.h"
#include "UnionFindExtra.h"
#include "recordPlace.h"

void printToEye(UnionFindExtra<int, int*, recordPlace>& uf){
  for (int i = 0; i < uf.used_size(); i++)
  {
    std::cout << " [" << i << " : " << (uf.get_validExtra(i)) << "] " << std::endl;;
  }
  std::cout << std::endl;
}
int main()
{
  UnionFindExtra<int, int*, recordPlace> uf;
  int a[1000];
  for (int i = 0; i < 1000; i++)
  {
    a[i] = i;
    uf.Insert(i, &a[i], recordPlace(i, i));
  }
  std::cout << uf;
  printToEye(uf);

  uf.Union(5,7);
  uf.Union(9,10);
  std::cout << uf;
  printToEye(uf);
  return 0;
}