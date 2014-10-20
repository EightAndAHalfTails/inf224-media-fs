#include "BaseObject.h"
#include "Video.h"
#include "Photo.h"
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
  
  Video* vid = new Video();
  Photo* pho = new Photo("My Photo", mktime(test), "/work/inf224/myfile", "Paris");

  vid->print();
  pho->print();

  return 0;
}
