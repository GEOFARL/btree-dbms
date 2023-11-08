#pragma once

#include <iostream>
#include <vector>

#include "../Models/Person.hpp"

using namespace std;

class BTreeNode
{
  vector<pair<string, Person *>> keys;
  vector<BTreeNode *> C;
  int t;
  int n;
  bool leaf;

public:
  BTreeNode(int _t, bool _leaf);
  ~BTreeNode();

private:
  bool remove(string key);
  void traverse();
  void insertNonFull(Person *person);
  void removeFromLeaf(int index);
  void removeFromNonLeaf(int index);

  // i – position of child y in int children array
  // this method should be called whenever a node is full
  void splitChild(int i, BTreeNode *y);

  void merge(int index);
  void fill(int index);

  int findKey(string &key);
  pair<string, Person *> &getPred(int index);
  pair<string, Person *> &getSucc(int index);

  void borrowFromPrev(int index);
  void borrowFromNext(int index);

  BTreeNode *search(string key);

  friend class BTree;
};