#include "initiation_dispatcher.h"

#include "event_handler.h"
#include "log.h"

#define MAX(a, b)   ((a) < (b) ? (b):(a))
namespace reactor{

InitiationDispatcher* InitiationDispatcher::instance_ = 0;

InitiationDispatcher::InitiationDispatcher() : fd_max_(0) {
  event_map_.clear();
  FD_ZERO(&read_fds_);
}

int InitiationDispatcher::register_handler(EventHandler *_event_handler, int _event_types) {
  if (!_event_handler) {
    LOG("_event_handler is NULL");
    return -1;
  }
  //intptr_t eh_ptr = reinterpret_cast<intptr_t>(_event_handler);
  int handle = _event_handler->get_handle();
  EventMapIter iter = event_map_.find(handle);
  if (iter == event_map_.end()) {
    event_map_.insert(EventPair(handle, EventInfo(_event_handler, _event_types)));
  } else {
    iter->second.event_types_ |= _event_types;
  }
  
  if (_event_types & ACCEPT_EVENT || _event_types & READ_EVENT) {
    FD_SET(handle, &read_fds_);
    fd_max_ = MAX(handle, fd_max_);
  }
  return 0;
}

int InitiationDispatcher::remove_handler(EventHandler *_event_handler, int _event_types) {
  if (!_event_handler)
  {
    LOG("_event_handler is NULL");
    return -1;
  }

  //intptr_t eh_ptr = reinterpret_cast<intptr_t>(_event_handler);
  int handle = _event_handler->get_handle();
  EventMapIter iter = event_map_.find(handle);

  if (iter == event_map_.end())
  {
    LOG("no such event, event type:%d", _event_types);
    return -1;
  }

  // clear bit 
  iter->second.event_types_ &= ~_event_types;  
  // remove from map if it has no more types
  if (iter->second.event_types_ == 0) {
    delete iter->second.handler_;
    event_map_.erase(iter);
  }

  // remove from read_fds_
  if (_event_types & READ_EVENT || _event_types & ACCEPT_EVENT)
    FD_CLR(handle, &read_fds_);

  return 0;
}

int InitiationDispatcher::handle_events(int _timeout) {
  struct timeval tv;
  tv.tv_sec = _timeout;

  if (select(fd_max_ + 1, &read_fds_, NULL, NULL, &tv) == -1) {
    LOG("select failed");
    perror("select");
    return -1;
  }

  for (int i = 0; i <= fd_max_; i++) {
    FD_ISSET(i, &read_fds_);
    EventMapIter iter = event_map_.find(i);
    if (iter == event_map_.end()) {
      LOG("fd doesn't corresponding to event map");
      return -1;
    }
    EventHandler* event_handler = iter->second.handler_;
    event_handler->handle_event(iter->second.event_types_);
  }
  return 0;
}

InitiationDispatcher* InitiationDispatcher::instance() {
  if (instance_ == 0)
    instance_ = new InitiationDispatcher();
  return instance_;
}

}
