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

string Film::toString(bool human_readable) const
{
  stringstream buf;
  if(human_readable)
    {
      buf << Video::toString()
	  << "Chapters:\t" << chapter_count << endl;
      if(chapters != NULL)
	{
	  for (int i=0; i<chapter_count; i++)
	    buf << "Chapter " << i << ":\t"
		<< chapters[i] / 60 << " minutes "
		<< chapters[i] % 60 << " seconds."
		<< endl;
	}
    }
  else
    {
      buf << Video::toString()
	  << "chapters " << chapter_count << " ";
      if(chapters != NULL)
	{
	  for (int i=0; i<chapter_count; i++)
	    buf << chapters[i] << " ";
	}
    }
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
  if(length != 0)
    {
      chapters = new int[length];
      for(int i=0; i<length; i++)
	chapters[i] = _chapters[i];
    }
  else
    chapters = NULL;
}
