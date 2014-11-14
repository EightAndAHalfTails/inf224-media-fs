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
  Photo(const std::string& name = "new photo",
	time_t creat = time(NULL),
	const std::string& path = "~/new_photo",
	const std::string& place = "" );

  //! Parameterless Destructor
  /*!
   * Implemetation is empty as there is nothing to delete.
   */
  virtual ~Photo();

  virtual std::string toString(void) const;

  virtual void play();
  
  // getters
  const std::string& getPlace(void) const; //!< getter for place

  //setters
  void setPlace(const std::string&); //!< setter for place

private:
  std::string place; //!< geographic location of photo
};

#endif
