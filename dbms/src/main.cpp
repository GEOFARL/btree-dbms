#include <iostream>
#include <string>
#include <vector>

#include "./BTree/BTree.hpp"
#include "./CLI/CommandManager.hpp"

#include "./CLI/Commands/Commands.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " command [options] [arguments]" << endl;
    return 1;
  }

  BTree btree(3);

  CommandManager manager;
  manager.registerCommand(make_unique<InsertCommand>(btree));
  manager.registerCommand(make_unique<PrintAllCommand>(btree));
  manager.registerCommand(make_unique<RemoveCommand>(btree));

  string commandName = argv[1];
  vector<string> commandArgs(argv + 2, argv + argc);

  manager.executeCommand(commandName, commandArgs);
  return 0;
}