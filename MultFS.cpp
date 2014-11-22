#include "MultFS.h"

intrusive_ptr<BaseObject> MultFS::create(BaseObject* ob)
{
  objects[ob->getName()] = ob;
  return ob;
}

intrusive_ptr<Group> MultFS::create(Group* g)
{
  groups[g->getName()] = g;
  return g;
}

void MultFS::remove(const std::string& n)
{
  // if n is object
  if (objects.find(n) != objects.end())
  {
    // delete object
    objects.erase(n);

    // delete object from every group in which it occurs
    for (groups_t::iterator it = groups.begin(); it != groups.end(); it++)
    {
      for (Group::iterator git = it->second->begin(); git != it->second->end(); git++)
      {
        if ((*git)->getName() == n)
        {
          it->second->erase(git);
        }
      }
    }
  }

  // if n is group
  if (groups.find(n) != groups.end())
  {
    groups.erase(n);
  }
}

void MultFS::search(const std::string& n)
{
  objects_t::iterator obfound = objects.find(n);
  groups_t::iterator gfound = groups.find(n);

  if (obfound != objects.end()){ obfound->second->print(); }

  if (gfound != groups.end()){ gfound->second->print(); }
}
void MultFS::play(const std::string& n)
{
  objects_t::iterator obfound = objects.find(n);
  groups_t::iterator gfound = groups.find(n);

  if (obfound != objects.end()){ obfound->second->play(); }

  if (gfound != groups.end()){ gfound->second->play(); }
}