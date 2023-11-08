#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../ICommand.hpp"
#include "../../DBMS/DBMS.hpp"

#include "../../Models/Person.hpp"

using namespace std;

class ModifyCommand : public ICommand
{
  DBMS &dbms;

public:
  ModifyCommand(DBMS &dbms) : dbms(dbms) {}
  virtual ~ModifyCommand() {}

  virtual void execute(const vector<string> &args) override
  {
    if (args.size() != 6)
    {
      cerr << "Usage: modify <key, id, fname, lname, city, age>" << endl;
      return;
    }

    int age, id;

    try
    {
      id = stoi(args[1]);
      age = stoi(args[5]);
    }
    catch (exception &e)
    {
      cerr << "Invalid age or id argument" << endl;
      dbms.save();
      exit(1);
    }

    string key = args[0];
    Person *person = new Person(id, args[2], args[3], args[4], age);
    bool modified = dbms.btree->modify(key, person);
    if (modified)
    {
      cout << "Modified: " << *person << endl;
    }
    else
    {
      cout << "Not found" << endl;
    }
  }
  virtual string name() const override { return "modify"; }
};
