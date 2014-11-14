#include "Video.h"
#include <ctime>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

Video::Video(const string& name, time_t creat, const string& path, int duration)
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

void Video::play()
{
  const string command = "mplayer " + getPath() + " &";
  system(command.c_str()); // execute command
}


// getters
int Video::getDuration(void) const { return duration; }

//setters
void Video::setDuration(int _duration) { duration = _duration; }
