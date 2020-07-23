#include <iostream>
#include <TimerEv.h>
using namespace std;

class TimerTest
{
public:
   bool timerCallback(TimerEv *)
   {
      cout << "Timer callback" << endl;
      return true; //return true for repeating timer and false for stopping the time
   }
};

int main()
{
   TimerTest *t = new TimerTest();
   TimerEv *ptimer = new TimerEv(3, 0);
   ptimer->bind(std::bind(&TimerTest::timerCallback, t, std::placeholders::_1));
   //ptimer->start();

   EventImpl *ev_obj = EventImpl::getInstance();
   if (ev_obj && ev_obj->initEv())
   {
      ptimer->start();
      ev_obj->dispatchEvloop();
   }

   return 0;
}
