#include "Group.h"
#include <string>
#include <iostream>

using namespace std;

Group::Group(){}
Group::Group(const string& n):name(n){}
Group::~Group(){}
const string& Group::getName() const { return name; }
void Group::print() const
{
  cout << name << ":" << endl
       << "============================" << endl;

  for(Group::const_iterator i = begin(); i != end(); i++)
    {
      (*i)->print();
      cout << "---------------------" << endl;
    }
  cout << "============================" << endl;
}

void Group::play() const
{
  for (Group::const_iterator i = begin(); i != end(); i++)
  {
    (*i)->play();
  }
}
