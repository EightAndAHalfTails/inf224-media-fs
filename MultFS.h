#ifndef MultFS_h
#define MultFS_h

#include "intrusive_ptr.h"
#include "BaseObject.h"
#include "Group.h"
#include <map>
#include <string>

using namespace std;

class MultFS 
{
private:
  typedef std::map < string, intrusive_ptr < Group > > groups_t;
  typedef std::map < string, intrusive_ptr < BaseObject > > objects_t;

  groups_t groups;
  objects_t objects;

public:

  intrusive_ptr<BaseObject> create(BaseObject*);
  intrusive_ptr<Group> create(Group*);
  void remove(const string&);
  void search(const string&);
  void play(const string&);
};
#endif