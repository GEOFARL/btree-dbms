#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "ICommand.hpp"

using namespace std;

class CommandManager
{
private:
  map<string, unique_ptr<ICommand>> commands;

public:
  void registerCommand(unique_ptr<ICommand> command);
  void executeCommand(const std::string &commandName, const std::vector<std::string> &args);
};