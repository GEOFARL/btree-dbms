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
    int maxId = -1;
    while (!file.eof())
    {
      vector<string> tokens = getLineSplitIntoTokens();
      if (tokens.size() == 0)
        continue;
      int id, age;
      try
      {
        id = stoi(tokens[0]);
        age = stoi(tokens[4]);
      }
      catch (exception &e)
      {
        cerr << "Error loading a file, invalid id or age" << endl;
        exit(1);
      }
      btree->insert(new Person(id, tokens[1], tokens[2], tokens[3], age));
      if (id > maxId)
        maxId = id;
    }
    Person::count = maxId;
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