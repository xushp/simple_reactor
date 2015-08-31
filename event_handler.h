#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_
namespace reactor {
class EventHandler {
 public:
  virtual void handle_event(EventType _et) = 0;
  virtual int get_handle(void) const = 0;
};
}
#endif
