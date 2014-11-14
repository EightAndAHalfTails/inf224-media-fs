#ifndef BaseObject_h
#define BaseObject_h

#include "intrusive_ptr.h"
#include <ctime>
#include <string>

//! Base multimedia-type file object
/*!
 * This class is the base class for all objects which describe
 * multimedia files in the project.
 */

class BaseObject: public Pointable {
public:

  //! Parameterless Constructor
  BaseObject();

  //! Parametered Constructor
  BaseObject(const std::string&, time_t, const std::string&);

  //! Parameterless Destructor
  /*!
   * Implemetation is empty as there is nothing to delete.
   */
  virtual ~BaseObject();

  //! Returns name of multimedia object (track name, movie title etc)
  const std::string& getName() const;

  //! Returns date of creation as time_t
  time_t getCreationDate() const;

  //! Returns unix path (including filename) of object
  const std::string& getPath() const;

  //! Sets name of multimedia object (track name, movie title etc)
  void setName(const std::string&);

  //! Sets date of creation as time_t
  void setCreationDate(time_t);

  //! Sets unix path (including filename) of object
  void setPath(const std::string&);

  //! Returns multi-line string containing formatted description of object
  virtual std::string toString() const;

  //! Prints formatted description of object
  /*! This function prints out a description of the object, usually by
   * displaying the values of each member variable. It does this by
   * calling the toString() function of the object. Thus that function
   * is virtual, so that subclasses of BaseObject can effectively
   * reimplement this function to include extra member data.
   */
  void print() const;

  //! Opens file in external player
  virtual void play() = 0;

private:
  std::string name; //!< name of multimedia object (track name, movie title etc)
  time_t creation_date; //!< date of creation
  std::string path; //!< unix path (including filename) of object
};

#endif
