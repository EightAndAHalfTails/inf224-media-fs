#ifndef Video_h
#define Video_h

#include "BaseObject.h"
#include <string>

//! Video file object
/*!
 * This class describes a Video object
 */

class Video : public BaseObject {
public:

  //! Parametered Constructor
  Video(std::string name = "new video",
	time_t creat = time(NULL),
	std::string path = "~/new_video",
	int duration = 0 );


  //! Parameterless Destructor
  /*!
   * Implemetation is empty as there is nothing to delete.
   */
  virtual ~Video();

  virtual std::string toString() const;

private:
  int duration; //! length of video
};

#endif
