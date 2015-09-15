#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include <iostream>

#include "initiation_dispatcher.h"
#include "net.h"
#include "event_handler.h"
#include "logging_acceptor.h"
#include "log.h"
using namespace std;

#define PORT 9888

int main()
{
  reactor::EventHandler *acceptor_handler = new reactor::LoggingAcceptor(PORT);
  for (;;) {
    reactor::InitiationDispatcher::instance()->handle_events(0);
    LOG("handle events restart");
  }
  
  
  /*
  net::SockStream sock;
  net::SockAcceptor acceptor(PORT);
  if (acceptor.init() == -1)
  {
    LOG("acceptor init fail");
    perror("acceptor init");
  }
  
  if (acceptor.accept_sock(sock) == -1) 
  {
    LOG("accept fail");
    perror("accept");
  }

  sock.recv_stream();
  */

  return 0;
}
