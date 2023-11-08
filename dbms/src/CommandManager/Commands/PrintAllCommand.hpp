#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../ICommand.hpp"
#include "../../DBMS/DBMS.hpp"

using namespace std;

class PrintAllCommand : public ICommand
{
  DBMS &dbms;

public:
  PrintAllCommand(DBMS &dbms) : dbms(dbms) {}
  virtual ~PrintAllCommand() {}

  virtual void execute(const vector<string> &args) override
  {
    if (!args.empty())
    {
      cerr << "Usage: print (no arguments)" << endl;
      return;
    }

    cout << "Printing values..." << endl;
    dbms.btree->traverse();
    cout << "Done!" << endl;
  }
  virtual string name() const override { return "print"; }
};
