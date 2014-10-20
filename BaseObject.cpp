#include "BaseObject.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


BaseObject::BaseObject(): name("new file"),
			  creation_date(time(NULL)),
			  path("~/newfile")
{}

BaseObject::BaseObject(string name, time_t creat, string path): name(name),
								creation_date(creat),
								path(path)
{}

BaseObject::~BaseObject()
{}

string BaseObject::getName() const { return name; }
time_t BaseObject::getCreationDate() const { return creation_date; }
string BaseObject::getPath() const { return path; }
void BaseObject::setName(std::string n) { name = n; }
void BaseObject::setCreationDate(time_t t) { creation_date = t; } 
void BaseObject::setPath(std::string p) { path = p; }

string BaseObject::toString() const
{
  stringstream buf;
  buf << "name: " << name << endl
      << "created: " << creation_date << endl
      << "path: " << path << endl;
  return buf.str();
}

void BaseObject::print() const
{
  cout << toString();
}
