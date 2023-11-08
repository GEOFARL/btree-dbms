#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "../BTree/BTree.hpp"
#include "Reader.hpp"
#include "Writer.hpp"

using namespace std;
namespace fs = std::filesystem;

const string dbFilePath = "./db/db.txt";

class DBMS
{
  const int T;

public:
  BTree *btree;

private:
  Reader reader;
  Writer writer;

public:
  DBMS() : T{10}, btree{new BTree(T)}, reader{btree, dbFilePath}, writer{btree, dbFilePath}
  {
  }
  ~DBMS()
  {
    save();
    delete btree;
  }

  void save()
  {
    writer.writeTree();
  }
};