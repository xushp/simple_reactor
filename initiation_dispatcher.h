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
  typedef std::map<intptr_t, int> EventMap;
  typedef std::map<intptr_t, int>::iterator EventMapIter;
  int register_handler(EventHandler *_eh, EventType _et);
  int remove_handler(EventHandler *_eh, EventType _et);
  int handle_events(int _timeout = 0); 
  static InitiationDispatcher* instance();
 private:
  InitiationDispatcher();
  static InitiationDispatcher *instance_;
  std::map<intptr_t, int> event_map_;
  int fd_max_;
  fd_set read_fds_;
};
}
#endif
