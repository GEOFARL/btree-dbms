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

private:
  void remove(int key);
  void traverse();
  void insertNonFull(int key);
  void removeFromLeaf(int index);
  void removeFromNonLeaf(int index);

  // i – position of child y in int children array
  // this method should be called whenever a node is full
  void splitChild(int i, BTreeNode *y);

  void merge(int index);
  void fill(int index);

  int findKey(int key);
  int getPred(int index);
  int getSucc(int index);

  BTreeNode *search(int key);

  friend class BTree;
};