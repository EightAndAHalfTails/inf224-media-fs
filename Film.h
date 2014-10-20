#ifndef Film_h
#define Film_h

#include "Video.h"
#include <string>

//! Film file object
/*!
 * This class describes a Film object
 */

class Film : public Video {
public:

  //! Parametered Constructor
  Film(std::string name = "new film",
       time_t creat = time(NULL),
       std::string path = "~/new_film",
       int duration = 0,
       int chapter_count = 1,
       int* chapters = NULL);


  //! Parameterless Destructor
  /*!
   * Implemetation is empty as there is nothing to delete.
   */
  virtual ~Film();

  virtual std::string toString() const;
  void setChapters(int*, int);
  void setChapterCount(int);
  const int* getChapters(void) const;
  int getChapterCount(void) const;

private:
  int duration; //! length of video
  int chapter_count; //! number of chapters in the film
  int* chapters; //! an array of integers describing the length of the chapters of the film
};

#endif
