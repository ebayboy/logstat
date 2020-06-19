

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "util.h"
#include "redisHelper.h"

//for test
#include "testRedisHelper.h"

using json = nlohmann::json;
using namespace std;

int main(int argc, char * const argv[])
{
    string c;

    readargs(argc, argv, c);

    cout << "config:" << c << endl;

    /* code */
    cout << "riskstat start..." << endl;

    readCfg("../conf/input.json");

    redisHelperTest();

    cout << "riskstat exit!" << endl;

    return 0;
}
