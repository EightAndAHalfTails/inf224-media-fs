#define SMART_PTR_DEBUG

#include "Video.h"
#include "Photo.h"
#include "Film.h"
#include "Group.h"
#include "intrusive_ptr.h"
#include "MultFS.h"
#include <string>

using namespace std;

int main( int argc, const char* argv[] )
{
  typedef intrusive_ptr<BaseObject> MultObj;
  typedef intrusive_ptr<Group> MultGr;


  time_t rawtime;
  time( &rawtime );
  struct tm y2k;
  y2k.tm_year = 100;
  y2k.tm_mon = 0;
  y2k.tm_mday = 1;
  y2k.tm_hour = 0;
  y2k.tm_min = 0;
  y2k.tm_sec = 0;
  y2k.tm_isdst = 0;

  time_t pasttime = mktime(&y2k);
  
  int cc = 5;
  int* chaps = new int[cc];
  chaps[0] = 60;
  chaps[1] = 45;
  chaps[2] = 120;
  chaps[3] = 30;
  chaps[4] = 95;

  int dur = 0;
  for(int i=0; i<cc; i++) dur += chaps[i];

  MultFS fs;

  MultObj avpvg = fs.create(new Film("Alien vs Predator vs Godzilla", pasttime, "~/Films/film1", dur, cc, chaps));
  MultObj tdohs = fs.create(new Film("The Disappearance of Haruhi Suzumiya", time(NULL), "~/Films/film2", 8888));
  MultObj twin = fs.create(new Video("Ore Twintail ni Narimasu - 01"));
  MultObj azu = fs.create(new Photo("azusa52435"));

  MultGr g = fs.create(new Group("anime"));
  g->push_back(tdohs);
  g->push_back(twin);
  g->push_back(azu);

  fs.search("anime");
  return 0;
}
