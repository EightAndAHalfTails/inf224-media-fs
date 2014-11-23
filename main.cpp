#define SMART_PTR_DEBUG

#include "Video.h"
#include "Photo.h"
#include "Film.h"
#include "Group.h"
#include "intrusive_ptr.h"
#include "MultFS.h"
#include "TCPServer.h"
#include <string>

using namespace std;

int main( int argc, const char* argv[] )
{
  TCPServer serv;
  const int port = 3331;
  return serv.run(port);
}
