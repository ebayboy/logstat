#include <iostream>
#include <TimerEv.h>
#include <exception>

using namespace std;

class TimerTest
{
public:
   TimerTest(string name) : m_name(name) {}
   ~TimerTest() {}

   bool timerCallback(TimerEv *)
   {
      cout << "Timer callback : m_name: " << m_name << endl;
      return true; //return true for repeating timer and false for stopping the time
   }

private:
   string m_name;
};

void addTimer()
{
   //init timer_event
   TimerTest *t = new TimerTest("fanpf");

   TimerEv *ptimer = new TimerEv(3, 0);
   ptimer->bind(std::bind(&TimerTest::timerCallback, t, std::placeholders::_1));
   ptimer->start();
}

int main()
{
   //init event_base
   EventImpl *ev_obj = EventImpl::getInstance(); //singleton
   if (ev_obj == nullptr || ev_obj->initEv() == false)
   {
      cerr << "Error: ev_obj init failed!" << endl;
      throw std::invalid_argument("ev_obj init failed!");
   }

   addTimer();

   ev_obj->dispatchEvloop();

   return 0;
}
