#include "Photo.h"
#include <string>
#include <ctime>
#include <sstream>
#include <cstdlib>

using namespace std;

Photo::Photo(const string& name, time_t creat, const string& path, const string& place)
  : BaseObject(name, creat, path),
    place(place)
{}

Photo::~Photo(){}

string Photo::toString() const
{
  stringstream buf;
  buf << BaseObject::toString() << "Location: " << place << endl;
  return buf.str();
}

void Photo::play()
{
  const string command = "eog " + getPath() + " &";
  system(command.c_str()); // execute command
}

// getters
const std::string& Photo::getPlace() const { return place; }

//setters
void Photo::setPlace(const std::string& _place) { place = _place; }
