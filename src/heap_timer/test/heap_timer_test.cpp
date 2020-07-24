#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include <bits/stdc++.h>

#include "../heap_timer.hpp"

using namespace std;

static time_heap min_heap(1024);

void timer_handler()
{
    min_heap.tick(); //定时处理任务
    /*获得堆顶的定时器，以它的定时时间设置alarm*/
    if (!min_heap.empty())
    {
        heap_timer *temp = min_heap.top();
        alarm(temp->expire - time(NULL)); //重新定时，以不断触发sigalarm信号
    }
}

//用户数据结构
struct client_data
{
    string name;
    heap_timer *timer;   //定时器
};

int main(int argc, const char *argv[])
{
    heap_timer *timer = new heap_timer(2 * TIMEOUT);
    client_data data;
    data.name = "fanpf";
    data.timer = 
    timer->function = cb_function;
    timer->user_data = &users[connfd];
    
    /*若该定时器为时间堆中第一个定时器，则设置alarm*/
    if (min_heap.empty())
    {
        alarm(2 * TIMEOUT);
    }

    min_heap.add_timer(timer);

    min_heap.adjust_timer(users[sockfd].timer, timeout);

    timer_handler();

    return 0;
}
