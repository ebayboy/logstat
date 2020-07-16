

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <thread>

#include "util.h"
#include "redisHelper.h"
#include "redisSubscriptHelper.h"

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

static void runTestCase(int argc, char **argv)
{
	string c = "../conf/riskstat.json";
	string d;

    readargs(argc, argv, c, d);

    cout << "config:" << c << endl;
    cout << "domain:" << d << endl;

    /* code */
    cout << "riskstat start..." << endl;

	//redisHelperTestInsertData();
	
	//vector<string> items;

	size_t hostSize = std::stoi(d);

	cout << "hostSize:" << hostSize << endl;

	pubStrContent(hostSize);

	/*
	hgetallContent("grp00_t.com.0_1590977640", items);
	for (auto i : items) {
		cout << i << endl;
	}
	*/

	exit(0);

    //redisHelperPublish();
}

int main(int argc, char * const argv[])
{
    func();

#if 0
	runTestCase();
#endif

    string c = "./conf/riskstat.json";
	string d;

    readargs(argc, argv, c, d);

    cout << "config:" << c << endl;

    /* code */
    cout << "riskstat start..." << endl;

    RiskConfig riskCfg(c);

    cout << "numstat:" << riskCfg.numstat << endl;

    return 0;
}
