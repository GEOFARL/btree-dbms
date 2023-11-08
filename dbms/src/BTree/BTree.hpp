#pragma once

#include <iostream>
#include "BTreeNode.hpp"

#include "../Models/Person.hpp"

using namespace std;

class BTree
{
  BTreeNode *root;
  int t;

public:
  BTree(int _t)
  {
    root = nullptr;
    t = _t;
  }

  ~BTree()
  {
    delete root;
  }

  void traverse()
  {
    if (root)
    {
      root->traverse();
    }
  }

  BTreeNode *search(string &k)
  {
    return (root == nullptr) ? nullptr : root->search(k);
  }

  void insert(Person *person);
  bool remove(string k);
  bool modify(string k, Person *person);
};