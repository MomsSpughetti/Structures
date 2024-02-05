#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "uf_test.h"

int main()
{
  // Create a UnionFind object
  UnionFind<int, std::string> uf;

  // Insert some elements and check that they are in their own sets
  uf.Insert(1, "one");
  uf.Insert(2, "two");
  uf.Insert(3, "three");
  uf.Insert(4, "four");
  uf.Insert(5, "five");
  assert(uf.Find(1)->key == 1);
  assert(uf.Find(2)->key == 2);
  assert(uf.Find(3)->key == 3);
  assert(uf.Find(4)->key == 4);
  assert(uf.Find(5)->key == 5);

  // Union some sets and check that Find returns the correct result
  uf.Union(1, 2);
  uf.Union(2, 3);
  uf.Union(3, 4);
  uf.Union(4, 5);
  assert(uf.Find(1)->key == uf.Find(2)->key);
  assert(uf.Find(2)->key == uf.Find(3)->key);
  assert(uf.Find(3)->key == uf.Find(4)->key);
  assert(uf.Find(4)->key == uf.Find(5)->key);
  assert(uf.Find(1)->key == uf.Find(5)->key);

  // Check that the get_size and get_capacity of the UnionFind object are correct
  assert(uf.get_size() == 5);
  assert(uf.get_capacity() >= 5);

  // Insert more elements and check that the get_capacity is increased if necessary
  uf.Insert(6, "six");
  uf.Insert(7, "seven");
  uf.Insert(8, "eight");
  uf.Insert(9, "nine");
  uf.Insert(10, "ten");
  assert(uf.get_size() == 10);
  assert(uf.get_capacity() >= 10);

  // Union all elements into a single set and check that Find returns the correct result
  uf.Union(1, 6);
  uf.Union(6, 7);
  uf.Union(7, 8);
  uf.Union(8, 9);
  uf.Union(9, 10);
  for (int i = 1; i <= 10; i++) {
    assert(uf.Find(1)->key == uf.Find(i)->key);
  }

  // Check that the get_size and get_get_capacity of the UnionFind object are unchanged
  assert(uf.get_size() == 10);
  // Check that the get_size and get_capacity of the UnionFind object are unchanged
  assert(uf.get_size() == 10);
  assert(uf.get_capacity() >= 10);

  // Check that Find returns the correct result for a large number of elements
  uf.Insert(11, "eleven");
  uf.Insert(12, "twelve");
  uf.Insert(13, "thirteen");
  uf.Insert(14, "fourteen");
  uf.Insert(15, "fifteen");
  uf.Insert(16, "sixteen");
  uf.Insert(17, "seventeen");
  uf.Insert(18, "eighteen");
  uf.Insert(19, "nineteen");
  uf.Insert(20, "twenty");
  uf.Union(1, 11);
  uf.Union(11, 12);
  uf.Union(12, 13);
  uf.Union(13, 14);
  uf.Union(14, 15);
  uf.Union(15, 16);
  uf.Union(16, 17);
  uf.Union(17, 18);
  uf.Union(18, 19);
  uf.Union(19, 20);
  for (int i = 1; i <= 20; i++) {
    assert(uf.Find(1)->key == uf.Find(i)->key);
  }

  // Check that the get_size and get_capacity of the UnionFind object are correct
  assert(uf.get_size() == 20);
  assert(uf.get_capacity() >= 20);

  std::cout << "All tests pass" << std::endl;
  return 0;
}
