#include <iostream>
#include "BTree.hpp"

using namespace std;

int main()
{
  BTree t(3);
  t.insert(10);
  t.insert(20);
  t.insert(5);
  t.insert(6);
  t.insert(12);
  t.insert(30);
  t.insert(7);
  t.insert(17);

  cout << "Traversal of the constructed tree is ";
  t.traverse();

  int k = 6;
  (t.search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";

  k = 15;
  (t.search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";
  cout << endl;
  return 0;
}