//
//  TCPServer.cpp: TCP/IP INET Server.
//  (c) Eric Lecolinet - Telecom ParisTech - 2013.
//  http://www.telecom-paristech.fr/~elc
//

#include "TCPServer.h"
#include "MultFS.h"
#include "Film.h"
#include "Video.h"
#include "Photo.h"
#include <unistd.h>
#include <iostream>
#include <sstream>
using namespace std;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Hook for TCPServer::startReadMessages() (see TCPServer::run())

struct TCPServerHook {
  TCPServerHook(TCPServer* _server, Socket* _sock)
  : server(_server), sock(_sock) {}
  TCPServer* server;
  Socket* sock;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

TCPServer::TCPServer() : servsock() {
  pthread_rwlock_init(&lock, NULL);
  /*
  // Add a few test objects and groups
  time_t rawtime;
  time( &rawtime );
  struct tm y2k;
  y2k.tm_year = 100;
  y2k.tm_mon = 0;
  y2k.tm_mday = 1;
  y2k.tm_hour = 0;
  y2k.tm_min = 0;
  y2k.tm_sec = 0;
  y2k.tm_isdst = 0;
  time_t pasttime = mktime(&y2k);
  
  int cc = 5;
  int* chaps = new int[cc];
  chaps[0] = 60;
  chaps[1] = 45;
  chaps[2] = 120;
  chaps[3] = 30;
  chaps[4] = 95;
  int dur = 0;
  for(int i=0; i<cc; i++) dur += chaps[i];
  
  MultFS::MultObj avpvg = fs.create(new Film("Alien_vs_Predator_vs_Godzilla", pasttime, "~/Films/film1", dur, cc, chaps));
  MultFS::MultObj tdohs = fs.create(new Film("The_Disappearance_of_Haruhi_Suzumiya", time(NULL), "~/Films/film2", 8888));
  MultFS::MultObj twin = fs.create(new Video("Ore_Twintail_ni_Narimasu_-_01"));
  MultFS::MultObj azu = fs.create(new Photo("azusa"));

  MultFS::MultGr g = fs.create(new Group("anime"));
  g->push_back(tdohs);
  g->push_back(twin);
  g->push_back(azu);
  */
}

TCPServer::~TCPServer() {}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int TCPServer::run(int port)
{
  // lier le ServerSocket a ce port
  int status = servsock.bind(port);
  
  if (status < 0) {
    cerr << "TCPServer: can't bind on port: "<<port<<" status="<<status<< endl;
    return status;  // valeur negative, voir Socket::bind()
  }

  // ignorer le signal SIGPIPE qui avorterait le serveur en cas d'erreur reseau
  servsock.ignoreSigPipe();
  
  while (true) {
    Socket* sock = servsock.accept();

    if (sock == NULL) {
      cerr << "TCPServer: accept() failed" << endl;
      continue;  // continue va a la prochaine iteration de while()
    }

    // lancer la lecture des messages de ce socket dans un thread.
    // pthread_create() cree un thread qui appelle la methode statique
    // startReadMessages() avec un argument de type (void*) qui est en fait
    // un TCPServerHook*. Ceci permet a startReadMessages() d'appeller la
    // methode d'instance readMessages() avec les argument adequats.

    TCPServerHook* hook = new TCPServerHook(this, sock);
    pthread_t tid;
    
    int status = pthread_create(&tid, NULL, startReadMessages, hook);
    if (status < 0)
      cerr << "TCPServer: pthread_create() failed" << endl;
  }
  
  pthread_exit(NULL);
  return 0;  // OK
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// called by pthread_create()

void* TCPServer::startReadMessages(void* _hook)
{
  TCPServerHook* hook = static_cast<TCPServerHook*>(_hook);
  hook->server->readMessages(hook->sock);
  delete hook;
  return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void TCPServer::readMessages(Socket* sock)
{
  SocketBuffer sockbuf(sock);
  
  while (true) {
    string message, response;
    
    // lire les données envoyées par le client
    // SocketBuffer::readLine() lit jusqu'au premier '\n' (qui est supprimé)
    ssize_t received = sockbuf.readLine(message);
    
    if (received < 0) {
      closeSocketAndThread(sock, "read error");
      continue;
    }
    
    if (received == 0) {
      closeSocketAndThread(sock, "connection closed by client");
      continue;
    }
    
    // traiter le message et retourner la reponse
    // ferme la connection si la valeur de retour est false
    if (! processMessage(message, response)) {
      closeSocketAndThread(sock, "closing connection with client");
      continue;
    }
    
    // toujours envoyer une reponse au client (sinon il va se bloquer)
    // SocketBuffer::writeLine() envoie tout et rajoute '\n'
    ssize_t sent = sockbuf.writeLine(response);
    
    if (sent < 0) {
      closeSocketAndThread(sock,"write error");
      continue;
    }
    
    if (sent == 0) {
      closeSocketAndThread(sock, "connection closed by client");
      continue;
    }
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void TCPServer::closeSocketAndThread(Socket* sock, const char* msg)
{
  cerr << "TCPServer: " << msg << " on socket: "<< sock << endl;
  delete sock;          // detruit le socket (NB: le destr fait sock.close())
  pthread_exit(NULL);   // termine le thread
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Traite le message 'message' et retourne la reponse 'response' ainsi qu'un
// booleen (par return) qui indique si la connection avec le client doit se
// poursuivre (true) ou etre fermée (false).
//
// Cette fonction peut etre executee en parallele par plusieurs threads sauf si
// le verrou 'lock' est bloqué en mode WRITE

bool TCPServer::processMessage(const string& message, string& response)
{
  // cette variable indique si la commande modifie les donnees du programme
  // par defaut on suppose que non
  bool change_data = false;

  stringstream msgstream(message);
  string command, arg;
  msgstream >> command >> arg;

  cout << "Received message '" << message << "'" << endl
       << "consisting of command " << command << endl
       << "and argument " << arg << endl;

  const string searchcmd = "search";
  const string playcmd = "play";
  const string createcmd = "add";
  const string writecmd = "write";
  const string readcmd = "read";
  
  // les commandes "add" et "read" modifient les donnees
  if (command == createcmd or command == readcmd) change_data = true;
  
  // suivant le cas, bloquer le verrou en mode WRITE ou en mode READ
  if (change_data)
    pthread_rwlock_wrlock(&lock);  // bloque en mode WRITE
  else
    pthread_rwlock_rdlock(&lock);  // bloque en mode READ

  if (command == searchcmd)
    {
      response = fs.search(arg);
    }
  else if (command == playcmd)
    {
      if (fs.play(arg)) response = "Playing";
      else response = "Not found";
    }
  else if (command == writecmd)
    {
      if(fs.write(arg))
	{
	  response = "Objects written to " + arg;
	}
      else
	{
	  response = "Error opening file";
	}
    }
  else if (command == readcmd)
    {
      int errors = fs.read(arg);
      if(errors >= 0)
	{
	  response = "Objects read from " + arg;
	  if (errors > 0)
	    {
	      stringstream errortext;
	      errortext << "Error: " << errors << " objects not read from " << arg; 
	      response = errortext.str();
	    }
	}
      else
	{
	  response = "Error opening file";
	}
    }
  else
    {
      response = "Command unrecognised: " + command;
    }
  
  // debloque le verrou (attention ne pas oublier cette ligne !)
  pthread_rwlock_unlock(&lock);

  // retourner false pour fermer la connexion
  return true;
}

