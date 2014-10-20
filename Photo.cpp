#include "Photo.h"
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

Photo::Photo(string name, time_t creat, string path, string place)
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