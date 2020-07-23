
#
#include <bits/stdc++.h>

#include "event2/event.h"
#include "event2/event_struct.h"
#include "event2/util.h"

#include "util.hpp"

struct event ev;
struct timeval tv;

void time_cb(int fd, short event, void *argc)
{
    std::cout << "time_cb: " << GetLocalTime(time(NULL)) << std::endl;
    event_add(&ev, &tv); // reschedule timer
}

int main()
{
    struct event_base *base = event_base_new();
    event_assign(&ev, base, -1, 0, time_cb, NULL);

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    event_add(&ev, &tv);

    event_base_dispatch(base);
}
