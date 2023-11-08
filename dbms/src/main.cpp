#include <iostream>
#include <string>
#include <vector>

#include "./CommandManager/CommandManager.hpp"
#include "./CommandManager/Commands/Commands.hpp"

#include "./DBMS/DBMS.hpp"

using namespace std;

int Person::count = 0;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " command [options] [arguments]" << endl;
    return 1;
  }

  DBMS dbms;

  CommandManager manager;
  manager.registerCommand(make_unique<InsertCommand>(dbms));
  manager.registerCommand(make_unique<ModifyCommand>(dbms));
  manager.registerCommand(make_unique<PrintAllCommand>(dbms));
  manager.registerCommand(make_unique<RemoveCommand>(dbms));
  manager.registerCommand(make_unique<SearchCommand>(dbms));

  string commandName = argv[1];
  vector<string> commandArgs(argv + 2, argv + argc);

  manager.executeCommand(commandName, commandArgs);
}