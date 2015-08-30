#ifndef REACTOR_INITIATION_DISPATCHER_H_
#define REACTOR_INITIATION_DISPATCHER_H_
/***********************************
 * Types of events handled by the 
 * Initiation_Dispatcher.
 * These values can be efficiently 
 * use or to form composite values.
 */
enum EventType{
  ACCEPT_EVENT = 01;
  READ_EVENT = 02;
  WRITE_EVENT = 04;
  TIMEOUT_EVENT = 010;
  SIGNAL_EVENT = 020;
  CLOSE_EVENT = 040;
};

class Event_Handler;
/*****************************
 * Demultiplex and dispatch 
 * Event_Handlers.
 */
class InitiationDispatcher{
 public:
  int register_handler(Event_Handler *eh, Event_Type et);
  int remove_handler(Event_Handler *eh, Event_Type et);
  int handler_events(int timeout = 0);  
};
#endif
