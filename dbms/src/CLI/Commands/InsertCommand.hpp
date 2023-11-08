#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../ICommand.hpp"
#include "../../BTree/BTree.hpp"

using namespace std;

class InsertCommand : public ICommand
{
  BTree &btree;

public:
  InsertCommand(BTree &tree) : btree(tree) {}
  virtual ~InsertCommand() {}

  virtual void execute(const vector<string> &args) override
  {
    if (args.size() != 1)
    {
      cerr << "Usage: insert <value>" << endl;
      return;
    }

    int value = std::stoi(args[0]);
    btree.insert(value);
    cout << "Inserted: " << value << endl;
  }
  virtual string name() const override { return "insert"; }
};
