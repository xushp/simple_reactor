#include "logging_acceptor.h"

namespace reactor {
LoggingAcceptor::LoggingAcceptor(int _port) : acceptor_(_port) {
  InitiationDispatcher::instance()->register_handler(this, ACCEPT_EVENT);
}

void LoggingAcceptor::handle_event(int _event_type) {
  if (!(_event_type & ACCEPT_EVENT)) {
    LOG("logging acceptor must be ACCEPT_EVENT");
    return;
  }

  net::SockStream new_connection;
  if (acceptor_.accept_sock(new_connection) == -1) {
    LOG("accept error");
    return;
  }

  LOG("client %d is comming", new_connection.get_handle());
  LoggingHandler *logging_handler = new LoggingHandler(new_connection);
}
}
