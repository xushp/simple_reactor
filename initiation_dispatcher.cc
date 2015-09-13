#include "initiation_dispatcher.h"

#include "event_handler.h"
#include "log.h"
#define MAX(a, b)   ((a) < (b) ? (b):(a))
namespace reactor{

InitiationDispatcher* InitiationDispatcher::instance_ = 0;

InitiationDispatcher::InitiationDispatcher() : fd_max_(0) {
  FD_ZERO(&read_fds_);
}

int InitiationDispatcher::register_handler(EventHandler *_eh, EventType _et) {
  if (!_eh)
    return -1;
  intptr_t eh_ptr = reinterpret_cast<intptr_t>(_eh);
  event_map_.insert(std::pair<intptr_t, int>(eh_ptr, _et));

  int handle = _eh->get_handle();
  if (_et & ACCEPT_EVENT || _et & READ_EVENT) {
    FD_SET(handle, &read_fds_);
    fd_max_ = MAX(handle, fd_max_);
  }
  return 0;
}

int InitiationDispatcher::remove_handler(EventHandler *_eh, EventType _et) {
  if (!_eh)
  {
    LOG("_eh is NULL");
    return -1;
  }

  intptr_t eh_ptr = reinterpret_cast<intptr_t>(_eh);
  std::map<intptr_t, int>::iterator it = event_map_.find(eh_ptr);

  if (it == event_map_.end())
  {
    LOG("no such event type:%d", _et);
    return -1;
  }

  // remove from read_fds_
  if (_et & READ_EVENT || _et & ACCEPT_EVENT)
    FD_CLR(_eh->get_handle(), &read_fds_);

  // remove from map
  it->second &= ~_et;
  if (it->second == 0)
    event_map_.erase(it);
  return 0;
}

int InitiationDispatcher::handle_events(int _timeout) {
  struct timeval tv;
  tv.tv_sec = _timeout;
  
  return 0;
}

InitiationDispatcher* InitiationDispatcher::instance() {
  if (instance_ == 0)
    instance_ = new InitiationDispatcher();
  return instance_;
}
}
