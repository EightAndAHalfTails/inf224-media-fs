#include "MultFS.h"
#include "Photo.h"
#include "Film.h"
#include "Video.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

MultFS::MultObj MultFS::create(BaseObject* ob)
{
  objects[ob->getName()] = ob;
  return ob;
}

MultFS::MultGr MultFS::create(Group* g)
{
  groups[g->getName()] = g;
  return g;
}

MultFS::MultObj MultFS::createObj(const string& s)
{
  MultObj obj;
  
  stringstream buf(s);
  string name, path, field;
  time_t creat;
  buf >> field >> name >> field >> creat >> field >> path;
  buf >> field;
  if(field == "location")
    {
      string loc;
      buf >> loc;
      obj = new Photo(name, creat, path, loc);
    }
  else if(field == "duration")
    {
      int dur;
      buf >> dur;
      buf >> field;
      if(field == "chapters")
	{
	  int cc;
	  buf >> cc;
	  int chaps[cc];
	  for(int i=0; i<cc; i++)
	    {
	      buf >> chaps[i];
	    }
	  obj = new Film(name, creat, path, dur, cc, chaps);
	}
      else
	{
	  obj = new Video(name, creat, path, dur);
	}
    }
  else
    {
      cout << "At line: " << s << endl;
      cout << "No object with field" << field << endl;
      obj = NULL;
    }
  return obj;
}

void MultFS::remove(const string& n)
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

string MultFS::search(const string& n) const
{
  objects_t::const_iterator obfound = objects.find(n);
  groups_t::const_iterator gfound = groups.find(n);

  if (obfound != objects.end()){ return obfound->second->toString(); }

  if (gfound != groups.end()){ return gfound->second->toString(); }

  return "No results";
}
bool MultFS::play(const string& n) const
{
  objects_t::const_iterator obfound = objects.find(n);
  groups_t::const_iterator gfound = groups.find(n);

  if (obfound != objects.end()){ obfound->second->play(); return true; }

  if (gfound != groups.end()){ gfound->second->play(); return true; }

  return false;
}

bool MultFS::write(const string& filename) const
{
  ofstream ofs;
  ofs.open(filename.c_str());

  if(!ofs.is_open())
    {
      cout << "Error opening file" << endl;
      return false;
    }
  for(objects_t::const_iterator it = objects.begin(); it != objects.end(); it++)
    {
      ofs << it->second->toString() << endl;
    }
  ofs.close();
  return true;
}

int MultFS::read(const string& filename)
{
  int errors = 0;
  ifstream ifs;
  ifs.open(filename.c_str());

  if(!ifs.is_open())
    {
      cout << "Error opening file" << endl;
      return -1;
    }
  while(ifs.good())
    {
      char buf[256];
      ifs.getline(buf, 256);

      string line = buf;
      if(line != "")
	{
	  MultObj ob = createObj(string(line));
	  if(objects.count(ob->getName()) == 0)
	    {
	      objects[ob->getName()] = ob;
	    }
	  else
	    {
	      cout << "Error: name exists" << endl;
	      errors++;
	    }
	}
    }
  ifs.close();
  return errors;
}
