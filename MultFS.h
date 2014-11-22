#ifndef MultFS_h
#define MultFS_h

#include "intrusive_ptr.h"
#include "BaseObject.h"
#include "Group.h"
#include <map>
#include <string>

using namespace std;

//! Top-Level Class for Multimedia Objects
/*!
* This class contains all the objects and groups in the program, and is responsible for destroying or creating them.
*/
class MultFS 
{
private:
  typedef std::map < string, intrusive_ptr < Group > > groups_t;
  typedef std::map < string, intrusive_ptr < BaseObject > > objects_t;

  groups_t groups;
  objects_t objects;

public:

  //! Adds a new object to the object container
  intrusive_ptr<BaseObject> create(BaseObject*);

  //! Adds a new group to the groups container
  intrusive_ptr<Group> create(Group*);

  //! Removes objects and groups by name
  void remove(const string&);

  //! Prints out details of objects and groups with the given name
  void search(const string&);

  //! Plays objects and groups with the given name
  void play(const string&);
};
#endif