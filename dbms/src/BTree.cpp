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
      // New root node
      BTreeNode *s = new BTreeNode(t, false);
      s->C[0] = root;
      s->splitChild(0, root);

      // New root has two children
      // We need to decide which one of the is going to have
      // a new key
      int i = 0;
      if (s->keys[0] < k)
      {
        i += 1;
      }
      s->C[i]->insertNonFull(k);

      root = s;
    }
    else
    {
      root->insertNonFull(k);
    }
  }
}