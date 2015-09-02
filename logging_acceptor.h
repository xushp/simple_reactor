#ifndef LOGGING_ACCEPTOR_H_
#define LOGGING_ACCEPTOR_H_
#include "net.h"
#include "event_handler.h"
namespace reactor{
class LoggingAcceptor : public EventHandler {
 public:
  LoggingAcceptor();
  virtual void handle_event(EventType _et);
  virtual int get_handle(void) const; 
  
 private:
  net::SockAcceptor acceptor_;
};
}
#endif

