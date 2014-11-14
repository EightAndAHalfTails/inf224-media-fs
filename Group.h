#ifndef Group_h
#define Group_h

#include <list>
#include <string>
#include "BaseObject.h"

//! Container Class for Multimedia Objects
/*!
 * This class gives a way to assign Multimedia Objects to a group.
 */

class Group: public std::list<BaseObject*>
{
public:
  //! Parameterless Constructor
  Group();
  
  //! Parametered Constructor
  Group(const std::string&);
  
  virtual ~Group();
  const std::string& getName() const;
  void print() const;
private:
  std::string name;
};

#endif
