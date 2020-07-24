
#include <mutex>

#include "EventImpl.h"

static std::mutex g_mutex;
EventImpl *EventImpl::m_pevObj = NULL;

EventImpl::EventImpl() : m_pevbase(NULL)
{
}

EventImpl::~EventImpl()
{
   if (m_pevbase)
      event_base_free(m_pevbase);
}

EventImpl *EventImpl::getInstance()
{
   if (!m_pevObj)
   {
      std::lock_guard<std::mutex> lock(g_mutex);
      if (!m_pevObj)
         m_pevObj = new EventImpl();
   }
   return m_pevObj;
}

bool EventImpl::initEv()
{
   m_pevbase = event_base_new();
   if (m_pevbase)
      return true;
   else
      return false;
}

void EventImpl::dispatchEvloop()
{
   event_base_dispatch(m_pevbase);
}

void EventImpl::attachFdtoEv(struct event *ev, int fd, event_callback_fn cb, void *cookie)
{
   event_assign(ev, m_pevbase, fd, EV_READ | EV_PERSIST, cb, cookie);
}

void EventImpl::addToEv(struct event *ev)
{
   event_add(ev, NULL);
}

void EventImpl::addToEv(struct event *ev, struct timeval *t_intvl)
{
   event_add(ev, t_intvl);
}
