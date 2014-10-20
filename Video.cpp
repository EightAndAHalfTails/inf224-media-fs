#include "Video.h"
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

Video::Video(string name, time_t creat, string path, int duration)
  : BaseObject(name, creat, path),
    duration(duration)
{}

Video::~Video(){}

string Video::toString() const
{
  stringstream buf;
  buf << BaseObject::toString() << "Duration: " << duration << endl;
  return buf.str();
}
