#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "../BTree/BTree.hpp"
#include "Reader.hpp"

using namespace std;
namespace fs = std::filesystem;

class DBMS
{
  const int T;
  BTree *btree;
  Reader reader;

public:
  DBMS() : T{10}, btree{new BTree(T)}, reader{btree}
  {
  }
  ~DBMS() { delete btree; }
};