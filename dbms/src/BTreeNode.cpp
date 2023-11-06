#include "BTreeNode.hpp"

BTreeNode::BTreeNode(int _t, bool _leaf)
{
  t = _t;
  leaf = _leaf;

  keys = new int[2 * t - 1];
  C = new BTreeNode *[2 * t];

  n = 0;
}