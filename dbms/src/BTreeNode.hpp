#pragma once;

#include <iostream>

using namespace std;

class BTreeNode
{
  int *keys;
  int t;
  BTreeNode **C;
  int n;
  bool leaf;

public:
  BTreeNode(int _t, bool _leaf);

  void traverse();
  BTreeNode *search(int key);
};