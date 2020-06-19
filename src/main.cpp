

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <thread>

#include <stdlib.h>
#include <unistd.h>

#include "util.h"
#include "redisHelper.h"
#include "redisSubscriptHelper.h"

//for test
#include "testRedisHelper.h"

using json = nlohmann::json;
using namespace std;


static void startRedisSub()
{
    cout << "thread start ..." << endl;

    reidsSubInit((char *)"127.0.0.1", 6379, (char *)"123456", (char *)"channel01");

    cout << "thread over ..." << endl;
}

int main(int argc, char * const argv[])
{
    string c;

    readargs(argc, argv, c);

    cout << "config:" << c << endl;

    /* code */
    cout << "riskstat start..." << endl;

    readCfg("../conf/input.json");

    redisHelperTest();

    thread t1(startRedisSub);
    t1.detach();

    for (int i = 0;; i++) {
        cout << "loop [" << i << "] times!" << endl;
        sleep(1);
    }

    cout << "riskstat exit!" << endl;

    return 0;
}
