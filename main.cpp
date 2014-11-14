#include "Video.h"
#include "Photo.h"
#include "Film.h"
#include "Group.h"
#include <string>

int main( int argc, const char* argv[] )
{
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

  Film* film1 = new Film("Alien vs Predator vs Godzilla", pasttime, "~/Films/film1", dur, cc, chaps);
  Film* film2 = new Film("The Disappearance of Haruhi Suzumiya", time(NULL), "~/Films/film2", 8888);
  Video* vid1 = new Video("Ore Twintail ni Narimasu - 01");
  Photo* pho1 = new Photo("azusa52435");

  Group anime("anime");
  Group films("films");

  anime.push_back(film2);
  anime.push_back(vid1);
  anime.push_back(pho1);

  films.push_back(film1);
  films.push_back(film2);

  anime.print();
  films.print();

  return 0;
}
