

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
	string d;

    readargs(argc, argv, c, d);

    cout << "config:" << c << endl;
    cout << "domain:" << d << endl;

    /* code */
    cout << "riskstat start..." << endl;

    readCfg("../conf/input.json");

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

	//exit 
	exit(0);

    //redisHelperPublish();

    return 0;
}
