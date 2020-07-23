//! @file   TimerEv.cpp
//! @brief  
//! @author Akhirul Islam
//!
#include <TimerEv.h>
#include <functional>

TimerEv::TimerEv(uint64_t secs, uint64_t usecs): m_secs(secs), m_usecs(usecs)
{
}

TimerEv::~TimerEv()
{

}

void TimerEv::bind(std::function<bool (TimerEv *)> fn)
{
   _callback = fn;
}

void TimerEv::start()
{
   EventImpl* event = EventImpl::getInstance();
   if(event)
   {
      event->attachFdtoEv( &m_event, -1, TimerEv::eventCallback, this);
      m_timeIntvl.tv_sec = m_secs;
      m_timeIntvl.tv_usec = m_usecs;
      event->addToEv(&m_event, &m_timeIntvl);
   }
}

void TimerEv::eventCallback(int fd, short event, void *cookie)
{
   TimerEv *timerEv = reinterpret_cast<TimerEv *>(cookie);
   timerEv->_callback(timerEv);
}
