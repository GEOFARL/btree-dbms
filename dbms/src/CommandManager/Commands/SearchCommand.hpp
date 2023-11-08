#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../ICommand.hpp"
#include "../../DBMS/DBMS.hpp"

#include "../../Models/Person.hpp"

using namespace std;

class SearchCommand : public ICommand
{
  DBMS &dbms;

public:
  SearchCommand(DBMS &dbms) : dbms(dbms) {}
  virtual ~SearchCommand() {}

  virtual void execute(const vector<string> &args) override
  {
    if (args.size() != 1)
    {
      cerr << "Usage: search <key>" << endl;
      return;
    }

    string key = args[0];
    Person *person = dbms.btree->searchPerson(key);

    if (!person)
    {
      cout << "Not Found" << endl;
    }
    else
    {
      cout << "Found: " << *person << endl;
    }
  }
  virtual string name() const override { return "search"; }
};
