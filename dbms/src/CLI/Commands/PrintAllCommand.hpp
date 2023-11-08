#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../ICommand.hpp"
#include "../../BTree/BTree.hpp"

using namespace std;

class PrintAllCommand : public ICommand
{
  BTree &btree;

public:
  PrintAllCommand(BTree &tree) : btree(tree) {}
  virtual ~PrintAllCommand() {}

  virtual void execute(const vector<string> &args) override
  {
    if (!args.empty())
    {
      cerr << "Usage: print (no arguments)" << endl;
      return;
    }

    cout << "Printing values..." << endl;
    btree.traverse();
  }
  virtual string name() const override { return "print"; }
};
