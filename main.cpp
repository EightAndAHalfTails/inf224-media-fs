#include "Video.h"
#include "Photo.h"
#include "Film.h"
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

  Film* film = new Film("Alien vs Predator vs Godzilla", pasttime, "~/Films/film1", dur, cc, chaps);
  Film* film_copy = new Film(*film);
  film->print();
  film_copy->print();

  cc = 2;
  chaps[0] = 120;
  chaps[1] = 600;
  film->setChapters(chaps, 2);
  film->print();
  film_copy->print();

  delete film;
  film_copy->print();


  return 0;
}
