#include "CommandManager.hpp"

void CommandManager::registerCommand(unique_ptr<ICommand> command)
{
  commands[string(command->name())] = move(command);
}

void CommandManager::executeCommand(const std::string &commandName, const std::vector<std::string> &args)
{
  if (commands.find(commandName) != commands.end())
  {
    commands[commandName]->execute(args);
  }
  else
  {
    std::cerr << "Command not found: " << commandName << std::endl;
  }
}
