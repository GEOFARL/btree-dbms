#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Person
{
  string fname;
  string lname;
  string city;
  int age;
  int id;
  static int count;

  Person(string fname, string lname, string city, int age)
      : fname{fname}, lname{lname}, city{city}, age{age}, id{++count} {}

  Person(int id, string fname, string lname, string city, int age)
      : fname{fname}, lname{lname}, city{city}, age{age}, id{id}
  {
    count += 1;
  }

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
