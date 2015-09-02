#include <stdio.h>
#include <string.h>
#include <stdarg.h>

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
  reactor::EventHandler *acceptor_handler = new reactor::LoggingAcceptor();
  /*
  net::InetAddr server_addr(PORT);
  reactor::LoggingAcceptor la;
  for (;;)
    reactor::InitiationDispatcher::instance()->handle_events();
  */
  return 0;
}
