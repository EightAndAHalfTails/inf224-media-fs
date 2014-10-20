#include "Film.h"
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

Film::Film(string name, time_t creat, string path, int duration, int cc, int* chaps)
  : Video(name, creat, path, duration),
    chapter_count(cc)
{
  chapters = new int[cc];
  for (int i=0; i<cc; i++)
      chapters[i] = chaps[i];
}

Film::~Film(){ delete chapters; }

string Film::toString() const
{
  stringstream buf;
  buf << Video::toString() << endl
      << "Chapters: " << chapter_count << endl;
  for (int i=0; i<chapter_count; i++)
    buf << "Chapter " << i << ": "
	<< chapters[i] / 60 << " minutes "
	<< chapters[i] % 60 << " seconds."
	<< endl;
  return buf.str();
}

void Film::setChapters(int* _chapters, int length)
{
  for(int i=0; i<length; i++)
    chapters[i] = _chapters[i];
}

const int* Film::getChapters(void) const { return chapters; }
int Film::getChapterCount(void) const { return chapter_count; }
