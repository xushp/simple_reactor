#ifndef LOGGING_ACCEPTOR_H_
#define LOGGING_ACCEPTOR_H_
#include "net.h"
#include "event_handler.h"
#include "logging_handler.h"
#include "log.h"
namespace reactor{
class LoggingAcceptor : public EventHandler {
 public:
  LoggingAcceptor();
  virtual void handle_event(int _event_type);
  virtual int get_handle(void) const; 
  
 private:
  net::SockAcceptor acceptor_;
};
}
#endif

