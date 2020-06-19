

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "util.h"
#include "redisHelper.h"

#include "testRedisHelper.h"

using json = nlohmann::json;
using namespace std;

static void testRedisHelper();

static void testRedisHelper()
{
    cout << "test redisHelper" << endl;

    HiredisHelper hi;
    string ip = "127.0.0.1";
    int port = 6379;
    string auth_str = "123456";
    int timeout = 200;
    hi.Init(ip, port, auth_str, timeout);

    int ret = addStrContent(hi);
}

int main(int argc, char * const argv[])
{
    string c;

    readargs(argc, argv, c);

    cout << "config:" << c << endl;

    /* code */
    cout << "riskstat start..." << endl;

    readCfg("../conf/input.json");

    testRedisHelper();

    cout << "riskstat exit!" << endl;

    return 0;
}
