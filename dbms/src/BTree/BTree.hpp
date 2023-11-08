#pragma once

#include <iostream>
#include <locale>
#include <algorithm>
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

  Person *searchPerson(string &k)
  {
    BTreeNode *node = search(k);
    if (!node)
    {
      return nullptr;
    }

    for (int i = 0; i < node->n; i++)
    {
      if (node->keys[i].first == k)
      {
        return node->keys[i].second;
      }
    }

    return nullptr;
  }

  void insert(Person *person);
  bool remove(string k);
  bool modify(string k, Person *person);
};