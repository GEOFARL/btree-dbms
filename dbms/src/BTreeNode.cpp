#include "BTreeNode.hpp"

BTreeNode::BTreeNode(int _t, bool _leaf)
{
  t = _t;
  leaf = _leaf;

  keys = new int[2 * t - 1];
  C = new BTreeNode *[2 * t];

  n = 0;
}

void BTreeNode::traverse()
{
  int i;
  for (i = 0; i < n; i++)
  {
    if (leaf == false)
    {
      C[i]->traverse();
    }
    cout << " " << keys[i];
  }

  if (leaf == false)
  {
    C[i]->traverse();
  }
}

BTreeNode *BTreeNode::search(int k)
{
  int i;
  while (i < n && k > keys[i])
  {
    i += 1;
  }

  if (keys[i] == k)
  {
    return this;
  }

  if (leaf)
  {
    return nullptr;
  }

  return C[i]->search(k);
}