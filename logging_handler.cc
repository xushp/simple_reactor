#include "logging_handler.h"

namespace reactor {
LoggingHandler::LoggingHandler(net::SockStream& _sock) : peer_stream_(_sock) {
  InitiationDispatcher::instance()->register_handler(this, READ_EVENT);
}

void LoggingHandler::handle_event(EventType _et) {
  if (_et == READ_EVENT) {
    peer_stream_.recv_stream();
  }
}
}
