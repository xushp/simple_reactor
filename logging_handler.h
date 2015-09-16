#ifndef LOGGING_HANDLER_H_
#define LOGGING_HANDLER_H_
#include "net.h" 
#include "event_handler.h"

namespace reactor {
class LoggingHandler : public EventHandler {
 public:
  LoggingHandler(net::SockStream&);
  virtual void handle_event(int _event_type);
  virtual int get_handle(void) const
  {
    return peer_stream_.get_handle();   
  }

 private:
  net::SockStream peer_stream_;
};
}
#endif
