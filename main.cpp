#include "Video.h"
#include "Photo.h"
#include "Film.h"
#include <string>

int main( int argc, const char* argv[] )
{
  time_t rawtime;
  time( &rawtime );
  struct tm * test = localtime ( &rawtime );
  test->tm_year = 30;
  test->tm_mon = 0;
  test->tm_mday = 1;
  test->tm_hour = 0;
  test->tm_min = 0;
  test->tm_sec = 0;

  time_t pasttime = mktime(test);
  
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
  film->print();

  cc = 2;
  delete chaps;
  film->print();

  return 0;
}
