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
    LOG("handle:%d, insert map", handle);
    event_map_.insert(EventPair(handle, EventInfo(_event_handler, _event_types)));
  } else {
    iter->second.event_types_ |= _event_types;
  }
  
  if (_event_types & ACCEPT_EVENT || _event_types & READ_EVENT) {
    LOG("handle:%d, fd_set handle", handle);
    FD_SET(handle, &read_fds_);
    fd_max_ = MAX(handle, fd_max_);
  }
  LOG("handle:%d added", handle);

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
  struct timeval *ptv = _timeout ? &tv : NULL;
  tv.tv_sec = _timeout;

  fd_set old_set = read_fds_;
  int trigger_cnt = 0;
  if ((trigger_cnt = select(fd_max_ + 1, &old_set, NULL, NULL, ptv)) == -1) {
    LOG("select failed");
    perror("select");
    return -1;
  }

  LOG("trigger cnt:%d", trigger_cnt);
  for (int i = 0; i <= fd_max_; i++) {
    if (FD_ISSET(i, &old_set)) {
      EventMapIter iter = event_map_.find(i);
      if (iter == event_map_.end()) {
        LOG("fd doesn't corresponding to event map");
        return -1;
      }
      EventHandler* event_handler = iter->second.handler_;
      event_handler->handle_event(iter->second.event_types_);
    }
  }
  return 0;
}

InitiationDispatcher* InitiationDispatcher::instance() {
  if (instance_ == 0)
    instance_ = new InitiationDispatcher();
  return instance_;
}

}
