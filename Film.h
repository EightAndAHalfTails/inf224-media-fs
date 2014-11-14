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
  Film(const std::string& name = "new film",
       time_t creat = time(NULL),
       const std::string& path = "~/new_film",
       int duration = 0,
       int chapter_count = 0,
       int* chapters = NULL);

  //! Copy Constructor
  Film(const Film&);

  //! Parameterless Destructor
  /*!
   * Deletes table of chapters.
   */
  virtual ~Film();

  virtual std::string toString() const;

  // setters
  void setChapters(const int*, int); //!< setter for chapters array. must also pass length of array, which sets ChapterCount

  // getters
  const int* getChapters(void) const; //!< getter for chapter array
  int getChapterCount(void) const; //!< getter for number of chapters

private:
  void makeChapters(const int*, int);
  int chapter_count; //!< number of chapters in the film
  int* chapters; //!< an array of integers describing the length of the chapters of the film
};

#endif
