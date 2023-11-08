#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../ICommand.hpp"
#include "../../DBMS/DBMS.hpp"

#include "../../Models/Person.hpp"

using namespace std;

class InsertCommand : public ICommand
{
  DBMS &dbms;

public:
  InsertCommand(DBMS &dbms) : dbms(dbms) {}
  virtual ~InsertCommand() {}

  virtual void execute(const vector<string> &args) override
  {
    if (args.size() != 4)
    {
      cerr << "Usage: insert <fname, lname, city, age>" << endl;
      return;
    }

    Person *person = new Person(args[0], args[1], args[2], stoi(args[3]));
    dbms.btree->insert(person);
    cout << "Inserted: " << *person << endl;
  }
  virtual string name() const override { return "insert"; }
};
