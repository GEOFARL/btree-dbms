#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../ICommand.hpp"
#include "../../BTree/BTree.hpp"

using namespace std;

class RemoveCommand : public ICommand
{
  BTree &btree;

public:
  RemoveCommand(BTree &tree) : btree(tree) {}
  virtual ~RemoveCommand() {}

  virtual void execute(const vector<string> &args) override
  {
    if (args.size() != 1)
    {
      cerr << "Usage: remove <value>" << endl;
      return;
    }

    int value = std::stoi(args[0]);
    bool removed = btree.remove(value);

    if (removed)
    {
      cout << "Removed: " << value << endl;
    }
    else
    {
      cout << "Value " << value << " not found" << endl;
    }
  }
  virtual string name() const override { return "remove"; }
};
