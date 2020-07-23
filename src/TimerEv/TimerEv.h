#ifndef _TIMER_EV_H_
#define _TIMER_EV_H_

#include <EventImpl.h>
#include <stdint.h>
#include <functional>

class TimerEv
{
public:
   TimerEv(uint64_t secs, uint64_t usecs);
   virtual ~TimerEv();
   void bind(std::function<bool(TimerEv *)> fn);
   void start();
   static void eventCallback(int fd, short event, void *cookie);

private:
   std::function<bool(TimerEv *)> _callback;
   uint64_t m_secs;
   uint64_t m_usecs;
   struct event m_event;
   struct timeval m_timeIntvl;
};

#endif
