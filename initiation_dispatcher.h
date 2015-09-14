#ifndef REACTOR_INITIATION_DISPATCHER_H_
#define REACTOR_INITIATION_DISPATCHER_H_

#include <sys/select.h>

#include <stdint.h>
#include <map>

/***********************************
 * Types of events handled by the 
 * Initiation_Dispatcher.
 * These values can be efficiently 
 * use or to form composite values.
 */
namespace reactor{
enum EventType {
  ACCEPT_EVENT = 01,
  READ_EVENT = 02,
  WRITE_EVENT = 04,
  TIMEOUT_EVENT = 010,
  SIGNAL_EVENT = 020,
  CLOSE_EVENT = 040,
};

class EventHandler;
/*****************************
 * Demultiplex and dispatch 
 * Event_Handlers.
 */
class InitiationDispatcher {
 public:
  struct EventInfo {
    EventHandler* handler_;
    int event_types_;
   public:
      EventInfo(EventHandler* _handler, int _types) : handler_(_handler) {
        event_types_ = static_cast<int>(_types);
      }
  };
  typedef std::map<int, EventInfo> EventMap;
  typedef std::map<int, EventInfo>::iterator EventMapIter;
  typedef std::pair<int, EventInfo> EventPair;
  int register_handler(EventHandler* _event_handler, int _event_types);
  int remove_handler(EventHandler* _event_handler, int _event_types);
  int handle_events(int _timeout = 0); 
  static InitiationDispatcher* instance();
 private:
  InitiationDispatcher();
  static InitiationDispatcher *instance_;
  int fd_max_;
  // event map and fd sets of select
  EventMap event_map_;
  fd_set read_fds_;
};
}
#endif
