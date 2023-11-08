#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>

#include "../BTree/BTree.hpp"

using namespace std;
namespace fs = std::filesystem;

class Reader
{
  BTree *btree;
  ifstream file;

public:
  Reader(BTree *btree, string path) : btree{btree}, file{path}
  {
    if (file)
      loadTree();
  }
  ~Reader() { file.close(); }

private:
  void loadTree()
  {
    while (!file.eof())
    {
      vector<string> tokens = getLineSplitIntoTokens();
      if (tokens.size() == 0)
        continue;
      btree->insert(new Person(stoi(tokens[0]), tokens[1], tokens[2], tokens[3], stoi(tokens[4])));
    }
  }

  vector<string> getLineSplitIntoTokens()
  {
    string line;

    vector<string> result;
    getline(file, line);

    stringstream lineStream(line);
    string cell;

    while (getline(lineStream, cell, ','))
    {
      result.push_back(cell);
    }

    return result;
  }
};