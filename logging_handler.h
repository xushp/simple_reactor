#ifndef LOGGING_HANDLER_H_
#define LOGGING_HANDLER_H_
namespace reactor {
class LoggingHandler : public EventHandler {
 public:
  LoggingHandler();
  virtual void handle_event(int _event_type);
  virtual int get_handle(void) const
  {
    return 0;   
  }

 private:
  net::SOCK_Stream peer_stream_;
};
}
#endif
