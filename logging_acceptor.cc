#include "logging_acceptor.h"

namespace reactor {
LoggingAcceptor::LoggingAcceptor() : acceptor_(0) {
  InitiationDispatcher::instance()->register_handler(this, ACCEPT_EVENT);
}

void LoggingAcceptor::handle_event(EventType _et) {
  if (_et != ACCEPT_EVENT) {
    LOG("logging acceptor must be ACCEPT_EVENT");
    return;
  }

  net::SockStream new_connection;
  if (acceptor_.accept_sock(new_connection) == -1) {
    LOG("accept error");
    return;
  }
  
  LoggingHandler *logging_handler = new LoggingHandler(new_connection);
}

int LoggingAcceptor::get_handle(void) const{
  return acceptor_.get_handle();
}
}
