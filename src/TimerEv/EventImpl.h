//EventImpl singleton

#ifndef __EVENTIMPL_H__
#define __EVENTIMPL_H__

#include <event2/event.h>
#include <event2/event_struct.h>

typedef void (*event_callback_fn)(int, short, void *);

class EventImpl
{
public:
   static EventImpl *getInstance();
   virtual ~EventImpl();
   void attachFdtoEv(struct event *, int, event_callback_fn, void *);
   void dispatchEvloop();
   bool initEv();
   void addToEv(struct event *ev);
   void addToEv(struct event *ev, struct timeval *t_intvl);
   struct event *getNewPersistentEvent(event_callback_fn cb, void *cookie);

private:
   EventImpl();
   EventImpl(const EventImpl &);

private:
   static EventImpl *m_pevObj;
   struct event_base *m_pevbase;
};
#endif
