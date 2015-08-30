#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_
class EventHandler {
 public:
  virtual int handle_event(EventType _et) = 0;
  virtual Handle get_handle(void) const = 0;
};
#endif
