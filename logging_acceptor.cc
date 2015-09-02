#include "logging_acceptor.h"

namespace reactor {
LoggingAcceptor::LoggingAcceptor() {
  InitiationDispatcher::instance()->register_handler(this, ACCEPT_EVENT);
}

void LoggingAcceptor::handle_event(EventType _et) {

}

int LoggingAcceptor::get_handle(void) const{
  return 0;
}

}
