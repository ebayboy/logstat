

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <thread>

#include "util.hpp"
#include "redisHelper/redisHelper.h"
#include "redisSubscriptHelper/redisSubscriptHelper.h"

#include "RiskConfig.hpp"

//for test
#include "testRedisHelper.h"

#include "func/func.h"

using json = nlohmann::json;
using namespace std;

static void startRedisSub()
{
    cout << "thread start ..." << endl;

    reidsSubInit((char *)"127.0.0.1", 6379, (char *)"123456", (char *)"channel01");

    cout << "thread over ..." << endl;
}

static void testOther()
{

#if 0
    /* code */
    cout << "riskstat start..." << endl;

    //redisHelperTestInsertData();

    //vector<string> items;

    //size_t hostSize = std::stoi(d);

    cout << "hostSize:" << hostSize << endl;

    pubStrContent(hostSize);

    /*
	hgetallContent("grp00_t.com.0_1590977640", items);
	for (auto i : items) {
		cout << i << endl;
	}
	*/

    //redisHelperPublish();
#endif
}

static void runTestCase(int argc, char **argv)
{
    string c = "../conf/riskstat.json";
    string d;

    readargs(argc, argv, c, d);

    cout << "config:" << c << endl;
    cout << "domain:" << d << endl;
}

class RiskStat
{
public:
    RiskStat(string cfgName);

    friend ostream &operator<<(ostream &output, const RiskStat &b)
    {
        output << "cfgName:" << b.cfgName << endl;
        output << "json.dump:" << b.j.dump() << endl;

        return output;
    }

private:
    RiskConfig *rc = nullptr;
    json j;
    string cfgName;
};

RiskStat::RiskStat(string cfgName) : cfgName(cfgName)
{
    ifstream fs(cfgName);
    if (fs.bad())
    {
        cerr << "Error: open file failed!" << endl;
        return;
    }

    fs >> this->j;

    fs.close();

    //parse RiskConfig
    auto rc = this->j.get<RiskConfig>();
    cout << "rc:" << rc << endl;
};

int main(int argc, char *const argv[])
{
    string c = "../conf/riskstat.json";
    string d;
    readargs(argc, argv, c, d);

    cout << "config:" << c << endl;

    RiskStat r(c);

    cout << "RiskStat: " << r << endl;

    /* code */
    cout << "riskstat start..." << endl;

    return 0;
}
