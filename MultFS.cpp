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

std::string MultFS::search(const std::string& n) const
{
  objects_t::const_iterator obfound = objects.find(n);
  groups_t::const_iterator gfound = groups.find(n);

  if (obfound != objects.end()){ return obfound->second->toString(); }

  if (gfound != groups.end()){ return gfound->second->toString(); }

  return "No results";
}
bool MultFS::play(const std::string& n) const
{
  objects_t::const_iterator obfound = objects.find(n);
  groups_t::const_iterator gfound = groups.find(n);

  if (obfound != objects.end()){ obfound->second->play(); return true; }

  if (gfound != groups.end()){ gfound->second->play(); return true; }

  return false;
}
