#include "Film.h"
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

Film::Film(const string& name, time_t creat, const string& path, int duration, int cc, int* chaps)
  : Video(name, creat, path, duration),
    chapter_count(cc)
{
  makeChapters(chaps, cc);
}

Film::Film(const Film& film)
  : Video(film),
    chapter_count(film.getChapterCount())
{
  makeChapters(film.getChapters(), film.getChapterCount());
}

Film::~Film(){ delete[] chapters; }

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

void Film::setChapters(const int* _chapters, int length)
{
  delete chapters;
  makeChapters(_chapters, length);
}

const int* Film::getChapters(void) const { return chapters; }
int Film::getChapterCount(void) const { return chapter_count; }

void Film::makeChapters(const int* _chapters, int length)
{
  chapter_count = length;
  chapters = new int[length];
  for(int i=0; i<length; i++)
    chapters[i] = _chapters[i];
}
