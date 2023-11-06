#pragma once

#include <iostream>
#include "BTreeNode.hpp"

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

  void traverse()
  {
    if (root)
    {
      root->traverse();
    }
  }

  BTreeNode *search(int k)
  {
    return (root == nullptr) ? nullptr : root->search(k);
  }

  void insert(int k);
};