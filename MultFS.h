#ifndef MultFS_h
#define MultFS_h

#include "intrusive_ptr.h"
#include "BaseObject.h"
#include "Group.h"
#include <map>
#include <string>

//! Top-Level Class for Multimedia Objects
/*!
* This class contains all the objects and groups in the program, and is responsible for destroying or creating them.
*/
class MultFS 
{
 public:
  //! Smart pointer to BaseObject
  typedef intrusive_ptr<BaseObject> MultObj;

  //! Smart pointer to Group
  typedef intrusive_ptr<Group> MultGr;

  //! Adds a new object to the object container. Depricated.
  MultObj create(BaseObject*);

  //! Adds a new group to the groups container. Depricated.
  MultGr create(Group*);

  MultObj createObj(const std::string&);
  MultGr createGr(const std::string&);

  //! Removes objects and groups by name
  void remove(const std::string&);

  //! Return a string containing details of objects and groups with the given name
  std::string search(const std::string&) const;

  //! Plays objects and groups with the given name
  bool play(const std::string&) const;

  //! Writes the list of objects to a file
  bool write(const std::string&) const;

  //! Reads in objects from a file
  bool read(const std::string&);
  
 private:
  typedef std::map < std::string, MultGr > groups_t;
  typedef std::map < std::string, MultObj > objects_t;

  groups_t groups;
  objects_t objects;

};
#endif
