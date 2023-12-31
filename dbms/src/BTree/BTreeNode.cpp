#include "BTreeNode.hpp"

BTreeNode::BTreeNode(int _t, bool _leaf)
{
  t = _t;
  leaf = _leaf;

  keys.reserve(2 * t - 1);
  C.reserve(2 * t);

  n = 0;
}

BTreeNode::~BTreeNode()
{
  for (int i = 0; i < n; i++)
  {
    delete C[i];
  }
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
    cout << *keys[i].second << endl;
  }

  if (leaf == false)
  {
    C[i]->traverse();
  }
}

BTreeNode *BTreeNode::search(string k, int &comparisons)
{
  int i{};
  comparisons += 1;
  while (i < n && caseInsensitiveStringCompare(keys[i].first, k))
  {
    comparisons += 1;
    i += 1;
  }

  comparisons += 1;
  if (keys[i].first == k)
  {
    return this;
  }

  comparisons += 1;
  if (leaf)
  {
    return nullptr;
  }

  return C[i]->search(k, comparisons);
}

void BTreeNode::insertNonFull(Person *person)
{
  // Index of rightmost element
  int i = n - 1;
  if (leaf) // Node is a leaf
  {
    // Find a place to insert and move all the
    // elements greater than a key one place ahead
    // while (i >= 0 && keys[i].first > person->fname)
    while (i >= 0 && caseInsensitiveStringCompare(person->fname, keys[i].first))
    {
      keys[i + 1] = keys[i];
      i -= 1;
    }

    // Inserts new key
    keys[i + 1] = make_pair(person->fname, person);
    n += 1;
  }
  else // Node is not a leaf
  {
    // Find a child that will have this new key
    // while (i >= 0 && keys[i].first > person->fname)
    while (i >= 0 && caseInsensitiveStringCompare(person->fname, keys[i].first))
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
      // if (keys[i + 1].first < person->fname)
      if (caseInsensitiveStringCompare(keys[i + 1].first, person->fname))
      {
        i += 1;
      }
    }

    C[i + 1]->insertNonFull(person);
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
int BTreeNode::findKey(string &k)
{
  int idx = 0;
  // while (idx < n && keys[idx].first < k)
  while (idx < n && caseInsensitiveStringCompare(k, keys[idx].first))
    ++idx;
  return idx;
}

bool BTreeNode::remove(string key)
{
  int idx = findKey(key);

  // The key to be removed is present in this node
  if (idx < n && keys[idx].first == key)
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
      return false;
    }

    bool inTheLastChild = (idx == n);

    if (C[idx]->n == t - 1)
    {
      fill(idx);
    }

    if (inTheLastChild && idx > n)
    {
      return C[idx - 1]->remove(key);
    }
    else
    {
      return C[idx]->remove(key);
    }
  }

  return true;
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
  string &key = keys[idx].first;

  // If the child that precedes key has at least t keys
  // Find the predecessor of key in the subtree rooted at
  // that child. Then replace k by its predecessor
  if (C[idx]->n > (t - 1))
  {
    pair<string, Person *> &pred = getPred(idx);
    keys[idx] = pred;
    C[idx]->remove(pred.first);
  }
  // If the left child doesn't have enough keys, examine
  // right child. If it has enough keys, replace current key
  // with its successor
  else if (C[idx + 1]->n > (t - 1))
  {
    pair<string, Person *> &succ = getSucc(idx);
    keys[idx] = succ;
    C[idx + 1]->remove(succ.first);
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

pair<string, Person *> &BTreeNode::getPred(int idx)
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

pair<string, Person *> &BTreeNode::getSucc(int idx)
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
    borrowFromNext(idx);
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

void BTreeNode::borrowFromNext(int idx)
{
  BTreeNode *child = C[idx];
  BTreeNode *sibling = C[idx + 1];

  child->keys[(child->n)] = keys[idx];

  if (!(child->leaf))
  {
    child->C[(child->n) + 1] = sibling->C[0];
  }

  keys[idx] = sibling->keys[0];

  for (int i = 1; i < sibling->n; i++)
  {
    sibling->keys[i - 1] = sibling->keys[i];
  }

  if (!sibling->leaf)
  {
    for (int i = 1; i <= sibling->n; ++i)
    {
      sibling->C[i - 1] = sibling->C[i];
    }
  }

  child->n += 1;
  sibling->n -= 1;
}

bool BTreeNode::modify(string key, Person *person)
{
  int comparisons{};
  BTreeNode *currentNode = search(key, comparisons);
  if (!currentNode)
  {
    return false;
  }

  for (int i = 0; i < currentNode->n; i++)
  {
    if (currentNode->keys[i].first == key)
    {
      Person *tmp = currentNode->keys[i].second;
      currentNode->keys[i].second = person;
      delete tmp;
      return true;
    }
  }
  return false;
}

bool BTreeNode::caseInsensitiveStringCompare(const std::string &str1, const std::string &str2)
{
  std::locale loc;
  return std::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end(),
                                      [&loc](char c1, char c2)
                                      {
                                        return std::tolower(c1, loc) < std::tolower(c2, loc);
                                      });
}