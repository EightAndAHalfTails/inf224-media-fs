#include "Group.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

Group::Group(){}
Group::Group(const string& n):name(n){}
Group::~Group(){}
const string& Group::getName() const { return name; }
void Group::print() const
{
  cout << toString();
}

string Group::toString() const
{
  stringstream str("");
  str << name << ":" << endl
      << "============================" << endl;

  for(Group::const_iterator i = begin(); i != end(); i++)
    {
      str << (*i)->toString();
      str << "---------------------" << endl;
    }
  str << "============================" << endl;

  return str.str();
}

void Group::play() const
{
  for (Group::const_iterator i = begin(); i != end(); i++)
  {
    (*i)->play();
  }
}
