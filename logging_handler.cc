#include "logging_handler.h"
#include "log.h"

namespace reactor {
LoggingHandler::LoggingHandler(net::SockStream& _sock) : peer_stream_(_sock) {
  InitiationDispatcher::instance()->register_handler(this, READ_EVENT);
}

void LoggingHandler::handle_event(int _event_type) {
  LOG("handl event,type:%d", _event_type);
  if (_event_type & READ_EVENT) {
    LOG("client %d's  message is comming", peer_stream_.get_handle());
    int count = peer_stream_.recv_stream();
    if (count == 0)
      handle_event(CLOSE_EVENT);
  } else if (_event_type & CLOSE_EVENT) {
    LOG("client close");
    InitiationDispatcher::instance()->remove_handler(this, READ_EVENT);
    //peer_stream_.close_stream();
  }
}
}
