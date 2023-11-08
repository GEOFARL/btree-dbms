#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "../BTree/BTree.hpp"

using namespace std;
namespace fs = std::filesystem;

class Writer
{
  BTree *btree;
  ofstream file;

public:
  Writer(BTree *btree, string path) : btree{btree}, file{path}
  {
  }
  ~Writer()
  {
    file.close();
  }

  void writeTree()
  {
    streambuf *coutbuf = cout.rdbuf();
    cout.rdbuf(file.rdbuf());

    btree->traverse();

    cout.rdbuf(coutbuf);
  }
};