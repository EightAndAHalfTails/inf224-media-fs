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

string Photo::toString(bool human_readable) const
{
  stringstream buf;
  if(human_readable)
    {
      buf << BaseObject::toString() << "Location:\t" << place << endl;
    }
  else
    {
      buf << BaseObject::toString()
	  << "location " << place << " ";
    }
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
