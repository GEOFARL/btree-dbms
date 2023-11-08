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
    if (args.size() != 5)
    {
      cerr << "Usage: modify <key, fname, lname, city, age>" << endl;
      return;
    }

    int age;

    try
    {
      age = stoi(args[4]);
    }
    catch (exception &e)
    {
      cerr << "Invalid age argument" << endl;
      dbms.save();
      exit(1);
    }

    string key = args[0];
    Person *person = new Person(args[1], args[2], args[3], age);
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
