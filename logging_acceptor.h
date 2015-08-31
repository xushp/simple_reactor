#ifndef LOGGING_ACCEPTOR_H_
#define LOGGING_ACCEPTOR_H_
namespace reactor{
class LoggingAcceptor : public EventHandler {
 public:
  LoggingAcceptor();
  virtual void handle_event(EventType _et);
  virtual int get_handle(void) const {
    //return accept_.get_handle();
    return 0;
  }
 
 private:
  net::SockAcceptor acceptor_;
};
}
#endif

