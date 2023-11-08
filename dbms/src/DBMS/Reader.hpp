#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "../BTree/BTree.hpp"

using namespace std;
namespace fs = std::filesystem;

class Reader
{
  BTree *btree;
  ifstream file;

public:
  Reader(BTree *btree) : btree{btree}, file{"./db/db.txt"}
  {
    if (file)
      loadTree();
  }
  ~Reader() { file.close(); }

private:
  void loadTree()
  {
    string line;
    while (getline(file, line))
    {
      cout << line << endl;
    }
  }
};