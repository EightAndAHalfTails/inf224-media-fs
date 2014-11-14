#include "BaseObject.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


BaseObject::BaseObject(): name("new file"),
			  creation_date(time(NULL)),
			  path("~/newfile")
{}

BaseObject::BaseObject(const string& name, time_t creat, const string& path):
  name(name),
  creation_date(creat),
  path(path)
{}

BaseObject::~BaseObject()
{}

const string& BaseObject::getName() const { return name; }
time_t BaseObject::getCreationDate() const { return creation_date; }
const string& BaseObject::getPath() const { return path; }
void BaseObject::setName(const std::string& n) { name = n; }
void BaseObject::setCreationDate(time_t t) { creation_date = t; } 
void BaseObject::setPath(const std::string& p) { path = p; }

string BaseObject::toString() const
{
  stringstream buf;
  buf << "name: " << name << endl
      << "created: " << ctime(&creation_date) << endl
      << "path: " << path << endl;
  return buf.str();
}

void BaseObject::print() const
{
  cout << toString();
}
