#include "initiation_dispatcher.h"

#include "event_handler.h"
#include "log.h"
namespace reactor{
InitiationDispatcher* InitiationDispatcher::instance_ = 0;
int InitiationDispatcher::register_handler(EventHandler *_eh, EventType _et) {
  if (!_eh)
    return -1;
  intptr_t eh_ptr = reinterpret_cast<intptr_t>(_eh);
  event_map_.insert(std::pair<intptr_t, int>(eh_ptr, _et));
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
  it->second &= ~_et;
  if (it->second == 0)
    event_map_.erase(it);
  return 0;
}

int InitiationDispatcher::handle_events(int _timeout) {
  return 0;
}

InitiationDispatcher* InitiationDispatcher::instance() {
  if (instance_ == 0)
    instance_ = new InitiationDispatcher();
  return instance_;
}
}
