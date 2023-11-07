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

void BTreeNode::insertNonFull(int key)
{
  // Index of rightmost element
  int i = n - 1;
  if (leaf) // Node is a leaf
  {
    // Find a place to insert and move all the
    // elements greater than a key one place ahead
    while (i >= 0 && keys[i] > key)
    {
      keys[i + 1] = keys[i];
      i -= 1;
    }

    // Inserts new key
    keys[i + 1] = key;
    n += 1;
  }
  else // Node is not a leaf
  {
    // Find a child that will have this new key
    while (i >= 0 && keys[i] > key)
    {
      i -= 1;
    }

    // If a child is full
    if (C[i + 1]->n == 2 * t - 1)
    {
      splitChild(i + 1, C[i + 1]);

      // After we've splitted a child, its middle
      // key will get to the keys array at i + 1 position
      // so we need to find out in which of the children
      // to insert a new key
      if (keys[i + 1] < key)
      {
        i += 1;
      }
    }

    C[i + 1]->insertNonFull(key);
  }
}

void BTreeNode::splitChild(int i, BTreeNode *y)
{
  // A new node that will store (t - 1) keys
  // of node y
  BTreeNode *z = new BTreeNode(y->t, y->leaf);
  z->n = t - 1;

  // Move last t - 1 items from y to z
  for (int j = 0; j < t - 1; j++)
  {
    z->keys[j] = y->keys[t + j];
  }

  // Copy the last t children of y to z
  if (!y->leaf)
  {
    for (int j = 0; j < t; j++)
    {
      z->C[j] = y->C[t + j];
    }
  }

  y->n = t - 1;

  // Now we need a space in this node for 'z' node
  for (int j = n; j > i; j--)
  {
    C[j + 1] = C[j];
  }

  C[i + 1] = z;
  // A key of y will be moved to this node,
  // so we need to free up some space
  for (int j = n - 1; j >= i; j -= 1)
  {
    keys[j + 1] = keys[j];
  }

  keys[i] = y->keys[t - 1];
  n += 1;
}