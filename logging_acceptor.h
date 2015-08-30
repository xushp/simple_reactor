#ifndef LOGGING_ACCEPTOR_H_
#define LOGGING_ACCEPTOR_H_
namespace reactor{
class LoggingAcceptor : public EventHandler {
 public:
  LoggingAcceptor();
  virtual void handle_event(EventType et);
  virtual HANDLE get_handle(void) const
  {
    return accept_.get_handle();
  }
 
 private:
  SockAcceptor acceptor_;
};
}
#endif

