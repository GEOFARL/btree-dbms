#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../ICommand.hpp"
#include "../../DBMS/DBMS.hpp"

using namespace std;

class RemoveCommand : public ICommand
{
  DBMS &dbms;

public:
  RemoveCommand(DBMS &dbms) : dbms(dbms) {}
  virtual ~RemoveCommand() {}

  virtual void execute(const vector<string> &args) override
  {
    if (args.size() != 1)
    {
      cerr << "Usage: remove <fname>" << endl;
      return;
    }

    string value = args[0];
    bool removed = dbms.btree->remove(value);

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
