#pragma once

#include <iostream>
#include <string>

using namespace std;

class Person
{
  int id;
  string &fname;
  string &lname;
  string &city;
  int age;
  static int count;

public:
  Person(string &fname, string &lname, string &city, int age)
      : fname{fname}, lname{lname}, city{city}, age{age}, id{++count} {}

  ~Person()
  {
    count -= 1;
  }

  friend ostream &operator<<(ostream &os, const Person &person)
  {
    os << person.id << "," << person.fname << "," << person.lname << "," << person.city << "," << person.age;
    return os;
  }
};

int Person::count = 0;
