#include "BTreeNode.hpp"

BTreeNode::BTreeNode(int _t, bool _leaf)
{
  t = _t;
  leaf = _leaf;

  keys = new int[2 * t - 1];
  C = new BTreeNode *[2 * t];

  n = 0;
}

BTreeNode::~BTreeNode()
{
  delete[] keys;

  for (int i = 0; i < n; i++)
  {
    delete C[i];
  }

  delete[] C;
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
  int i{};
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

// A utility function that returns the index of the first key that is
// greater than or equal to k
int BTreeNode::findKey(int k)
{
  int idx = 0;
  while (idx < n && keys[idx] < k)
    ++idx;
  return idx;
}

void BTreeNode::remove(int key)
{
  int idx = findKey(key);

  // The key to be removed is present in this node
  if (idx < n && keys[idx] == key)
  {
    if (leaf)
    {
      removeFromLeaf(idx);
    }
    else
    {
      removeFromNonLeaf(idx);
    }
  }
  else
  {
    // This node is a leaf, so key is not present
    if (leaf)
    {
      cout << "The key " << key << " does not exist on the tree" << endl;
    }

    bool inTheLastChild = (idx == n);

    if (C[idx]->n == t - 1)
    {
      fill(idx);
    }

    C[idx]->remove(key);
  }
}

void BTreeNode::removeFromLeaf(int idx)
{
  for (int i = idx + 1; i < n; i++)
  {
    keys[i - 1] = keys[i];
  }

  n -= 1;
}

void BTreeNode::removeFromNonLeaf(int idx)
{
  int key = keys[idx];

  // If the child that precedes key has at least t keys
  // Find the predecessor of key in the subtree rooted at
  // that child. Then replace k by its predecessor
  if (C[idx]->n > (t - 1))
  {
    int pred = getPred(idx);
    keys[idx] = pred;
    C[idx]->remove(pred);
  }
  // If the left child doesn't have enough keys, examine
  // right child. If it has enough keys, replace current key
  // with its successor
  else if (C[idx + 1]->n > (t - 1))
  {
    int succ = getSucc(idx);
    keys[idx] = succ;
    C[idx + 1]->remove(succ);
  }
  // Left and Right children have t - 1 keys
  // We need to merge them and add this key in the middle
  // Then remove that key from newly created node
  else
  {
    merge(idx);
    C[idx]->remove(key);
  }
}

int BTreeNode::getPred(int idx)
{
  // Find the rightmost node that is the leaf
  BTreeNode *cur = C[idx];
  while (!cur->leaf)
  {
    cur = cur->C[cur->n];
  }

  // Last key of the leaf
  return cur->keys[cur->n - 1];
}

int BTreeNode::getSucc(int idx)
{
  // Find the leftmost node that is the leaf
  BTreeNode *cur = C[idx + 1];
  while (!cur->leaf)
  {
    cur = cur->C[0];
  }

  // Return the first key of the leaf
  return cur->keys[0];
}

void BTreeNode::merge(int idx)
{
  BTreeNode *child = C[idx];
  BTreeNode *sibling = C[idx + 1];

  // Pull the current key and insert it at the end of
  // the current node
  child->keys[t - 1] = keys[idx];

  // Copy keys from sibling to child
  for (int i = 0; i < sibling->n; i++)
  {
    child->keys[t + i] = sibling->keys[i];
  }

  // Copy child pointers
  if (!child->leaf)
  {
    for (int i = 0; i <= sibling->n; i++)
    {
      child->C[t + i] = sibling->C[i];
      sibling->C[i] = nullptr;
    }
  }

  // Remove key from the current node
  for (int i = idx + 1; i < n; i++)
  {
    keys[i - 1] = keys[i];
  }

  // Remove one child from the current node
  for (int i = idx + 2; i <= n; i++)
  {
    C[i - 1] = C[i];
  }

  child->n += sibling->n + 1;
  n -= 1;

  delete sibling;
  return;
}

void BTreeNode::fill(int idx)
{
  // If the previous child has more than t - 1 keys
  // Borrow a key from that child
  if (idx != 0 && C[idx - 1]->n > t - 1)
  {
    borrowFromPrev(idx);
  }
  // If the next child has more than t - 1 keys
  // Borrow a key from that child
  else if (idx != n && C[idx + 1]->n > t - 1)
  {
    // TODO: Borrow from next child
  }
  // Both children do not have enough keys, so merge them
  else
  {
    if (idx != n)
    {
      merge(idx);
    }
    else
    {
      merge(idx - 1);
    }
  }
}

void BTreeNode::borrowFromPrev(int idx)
{
  BTreeNode *child = C[idx];
  BTreeNode *sibling = C[idx - 1];

  for (int i = child->n - 1; i >= 0; i--)
  {
    child->keys[i + 1] = child->keys[i];
  }

  if (!child->leaf)
  {
    for (int i = child->n; i >= 0; i--)
    {
      child->C[i + 1] = child->C[i];
    }
  }

  child->keys[0] = keys[idx - 1];

  if (!child->leaf)
  {
    child->C[0] = sibling->C[sibling->n];
  }

  keys[idx - 1] = sibling->keys[sibling->n - 1];

  child->n += 1;
  sibling->n -= 1;
}