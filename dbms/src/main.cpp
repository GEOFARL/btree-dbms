#include <iostream>
#include <string>
#include <vector>

#include "./BTree/BTree.hpp"
// #include "./CLI/CommandManager.hpp"

// #include "./CLI/Commands/Commands.hpp"

// #include "./DBMS/DBMS.hpp"

#include "./Models/Person.hpp"

using namespace std;

int Person::count = 0;

int main(int argc, char *argv[])
{
  // if (argc < 2)
  // {
  //   cerr << "Usage: " << argv[0] << " command [options] [arguments]" << endl;
  //   return 1;
  // }

  // BTree btree(3);

  // CommandManager manager;
  // manager.registerCommand(make_unique<InsertCommand>(btree));
  // manager.registerCommand(make_unique<PrintAllCommand>(btree));
  // manager.registerCommand(make_unique<RemoveCommand>(btree));

  // string commandName = argv[1];
  // vector<string> commandArgs(argv + 2, argv + argc);

  // manager.executeCommand(commandName, commandArgs);

  // cout << argc << endl;
  // for (int i = 0; i < argc; i++)
  // {
  //   cout << argv[i] << endl;
  // }
  // DBMS dbms;

  BTree t(3); // A B-Tree with minimum degree 3

  t.insert(new Person("Maxim", "Tsyganok", "Kyiv", 18));
  t.insert(new Person("Artem", "Hrytsenko", "Romny", 18));
  t.insert(new Person("Roman", "Piznak", "Drohobych", 18));
  t.insert(new Person("Maxim", "Poplavskiy", "Zhytomir", 18));

  cout << "Traversal of tree constructed is\n";
  t.traverse();
  cout << endl;

  t.remove("Maxim");
  cout << "Traversal of tree after removing Maxim\n";
  t.traverse();
  cout << endl;

  cout << endl;
  return 0;
}