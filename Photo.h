#ifndef Photo_h
#define Photo_h

#include "BaseObject.h"
#include <string>

//! Photo file object
/*!
 * This class describes a Photo object
 */

class Photo : public BaseObject {
public:

  //! Parametered Constructor
  Photo(std::string name = "new photo",
	time_t creat = time(NULL),
	std::string path = "~/new_photo",
	std::string place = "" );

  //! Parameterless Destructor
  /*!
   * Implemetation is empty as there is nothing to delete.
   */
  virtual ~Photo();

  virtual std::string toString() const;
private:
  std::string place; //! geographic location of photo
};

#endif
