#include "BTree.hpp"

void BTree::insert(int k)
{
  if (!root)
  {
    root = new BTreeNode(t, true);
    root->keys[0] = k;
    root->n = 1;
  }
  else
  {
    if (root->n == 2 * t - 1)
    {
      // TODO: IMPLEMENT SPLITING
    }
    else
    {
      // TODO: IMPLEMENT INSERTING IN A NON FULL NODE
    }
  }
}