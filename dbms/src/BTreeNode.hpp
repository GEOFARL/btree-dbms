#pragma once

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
  ~BTreeNode();

  void traverse();
  void insertNonFull(int key);
  // i – position of child y in int children array
  // this method should be called whenever a node is full
  void splitChild(int i, BTreeNode *y);

  BTreeNode *search(int key);

  friend class BTree;
};