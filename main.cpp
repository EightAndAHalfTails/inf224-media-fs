#define SMART_PTR_DEBUG

#include "Video.h"
#include "Photo.h"
#include "Film.h"
#include "Group.h"
#include "intrusive_ptr.h"
#include <string>

using namespace std;

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

  intrusive_ptr<Film> film1 = new Film("Alien vs Predator vs Godzilla", pasttime, "~/Films/film1", dur, cc, chaps);
  intrusive_ptr<Film> film2 = new Film("The Disappearance of Haruhi Suzumiya", time(NULL), "~/Films/film2", 8888);
  intrusive_ptr<Video> vid1 = new Video("Ore Twintail ni Narimasu - 01");
  intrusive_ptr<Photo> pho1 = new Photo("azusa52435");

  Group* anime = new Group("anime");
  Group* films = new Group("films");

  anime->push_back(film2);
  anime->push_back(vid1);
  anime->push_back(pho1);

  films->push_back(film1);
  films->push_back(film2);

  anime->print();
  films->print();

  cout << "Setting pointers to NULL...";
  film1 = NULL;
  film2 = NULL;
  vid1 = NULL;
  cout << "Done" << endl;

  cout << "Deleting anime" << endl;
  delete anime;

  cout << "Deleting films" << endl;
  delete films;

  cout << "Deleting last photo" << endl;
  pho1 = NULL;

  cout << "End of Program" << endl;
  return 0;
}
