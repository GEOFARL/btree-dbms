#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ICommand
{
public:
  virtual ~ICommand() {}

  virtual void execute(const vector<string> &args) = 0;
  virtual string name() const = 0;
};
