
#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <vector>
#include <fstream>

#include <time.h>
#include <unistd.h>

#include "redisHelper.h"

#include "testRedisHelper.h"

using namespace std;

// hiredis官方： https://github.com/redis/hiredis/

#define CHECK_FREE_REDIS_REPLY(reply) \
	if (reply) {\
		freeReplyObject(reply);\
		return 0;   \
	} else {\
		cout << "freeReplyObject Fail" << endl;\
		return -1; \
	}

//PUBLISH channel01 "grp00_t.com_1590977640"
int pubStrContent(size_t hostSize) {

	HiredisHelper redis_conn;
	redis_conn.Init("127.0.0.1", 6379, "123456", 200);

	for (size_t i = 0; i < hostSize; i++)
	{
		ostringstream oss;
		oss << "grp00_t.com." << i << "_1590977640";

		stringstream ss_cmd;
		ss_cmd << "PUBLISH channel01 " << oss.str();

		string cmd = ss_cmd.str();
		redisReply *reply = redis_conn.ExecuteCmd(cmd);
		if (reply) {
			cout << "push redis succ " << cmd << endl;
		} else {
			cout << "push redis fail " << cmd << endl;
		}
		if (reply) {
			freeReplyObject(reply);
		} else  {
			cout << "freeReplyObject Fail" << endl;
		}

		usleep(200);
	}

	return 0;
}

// set "cloudox" "boy"
static int addStrContent(HiredisHelper &redis_conn) {
	string m_redis_key = "cloudox";
	stringstream ss_cmd;
	ss_cmd << "SET " << m_redis_key;
	ss_cmd << " " << "boy";

	string cmd = ss_cmd.str();
	redisReply *reply = redis_conn.ExecuteCmd(cmd);
	if (reply) {
		cout << "push redis succ " << cmd << endl;
		return 0;
	} else {
		cout << "push redis fail " << cmd << endl;
		return -1;
	}
	CHECK_FREE_REDIS_REPLY(reply);
}

//GET "cloudox"
static int getStrContent(HiredisHelper &redis_conn, string &item) {
	string m_redis_key = "cloudox";
	stringstream ss_cmd;
	ss_cmd << "GET " << m_redis_key;

	string cmd = ss_cmd.str();
	redisReply *reply = redis_conn.ExecuteCmd(cmd);
	if (reply && reply->type == REDIS_REPLY_STRING) {
		item = reply->str;
		return 0;
	} else {
		cout << "get redis fail " << cmd << endl;
		return -1;
	}
	CHECK_FREE_REDIS_REPLY(reply);
}

//ZADD cloudox 1 body
static int addZsetContent(HiredisHelper &redis_conn) {
	string m_redis_key = "cloudox";
	stringstream ss_cmd;
	ss_cmd << "ZADD " << m_redis_key;
	ss_cmd << " " << "1" << " " << "boy";

	string cmd = ss_cmd.str();
	redisReply *reply = redis_conn.ExecuteCmd(cmd);
	if (reply) {
		cout << "push redis succ " << cmd << endl;
		return 0;
	} else {
		cout << "push redis fail " << cmd << endl;
		return -1;
	}
	CHECK_FREE_REDIS_REPLY(reply);
}

static int getZsetContent(HiredisHelper &redis_conn, vector<string> &items) {
	string m_redis_key = "cloudox";
	stringstream ss_cmd;
	ss_cmd << "ZRANGEBYSCORE " << m_redis_key << " -inf " << "5" << " limit 0 10"; 
	// 取负无穷~5分值内的从第一个开始的十个值。

	string cmd = ss_cmd.str();
	redisReply *reply = redis_conn.ExecuteCmd(cmd);
	if (reply && reply->type == REDIS_REPLY_ARRAY) {
		cout << "reply size:" << reply->elements << endl;
		for (size_t i = 0; i < reply->elements; ++i) {
			if (NULL != reply->element[i]) {
				redisReply *ele = reply->element[i];
				if (ele->type == REDIS_REPLY_INTEGER) {
					items.push_back(to_string(ele->integer));// C++11
				} else if (ele->type == REDIS_REPLY_STRING) {
					string s(ele->str, ele->len);
					items.push_back(s);
				}
			}
		}

		return 0;
	} else {
		cout << "get redis fail " << cmd << endl;
		return -1;
	}
	CHECK_FREE_REDIS_REPLY(reply);
}

//HGETALL grp00_t.com_1590977640
int hgetallContent(string m_redis_key, vector<string> &items) {
	HiredisHelper redis_conn;
	string ip = "127.0.0.1";
	int port = 6379;
	string auth_str = "123456";
	int timeout = 200;
	redis_conn.Init(ip, port, auth_str, timeout);


	stringstream ss_cmd;
	ss_cmd << "HGETALL " << m_redis_key;

	string cmd = ss_cmd.str();
	redisReply *reply = redis_conn.ExecuteCmd(cmd);
	if (reply && reply->type == REDIS_REPLY_ARRAY) {
		cout << "reply size:" << reply->elements << endl;
		for (size_t i = 0; i < reply->elements; ++i) {
			if (NULL != reply->element[i]) {
				redisReply *ele = reply->element[i];
				if (ele->type == REDIS_REPLY_INTEGER) {
					items.push_back(to_string(ele->integer));// C++11
				} else if (ele->type == REDIS_REPLY_STRING) {
					string s(ele->str, ele->len);
					items.push_back(s);
				}
			}
		}

		return 0;
	} else {
		cout << "get redis fail " << cmd << endl;
		return -1;
	}
	CHECK_FREE_REDIS_REPLY(reply);
}

static void  getCmds(std::vector<string> &cmds, size_t hostSize, size_t ipsSize)
{

	//HSET grp00_t.com_1590977400 1.1.1.1 "11|00|33|44|55|66|77"
	string tms[] = { "1590977400", "1590977460", "1590977520", "1590977580", "1590977640"};
	string split = "_";
	string grpid = "grp00";
	string vals[] = { "11|11|11|11|11|11", "22|22|22|22|22|22", "33|33|33|33|33|33", "44|44|44|44|44|44", "55|55|55|55|55|55"};

	//HSET grp00_t.com_
	std::vector<string> keys;
	std::vector<string> ips;

	for (size_t i = 0; i < hostSize; i++)
	{
		ostringstream oss;
		oss << "grp00_" << "t.com." << i << "_";
		keys.push_back(oss.str());
	}

	//生成ip地址
	//1-254.1.1.1-254
	for (size_t k = 1; k < 254 && ips.size() < ipsSize; k++)
	{
		for (size_t m = 1; m < 254 && ips.size() < ipsSize; m++) {
			ostringstream oss;
			oss << k << ".1.1." << m;
			ips.push_back(oss.str());
		}
	}


	//遍历 keys ips vals
	//key :  grp00_t.com_1590977400 
	for(size_t i=0; i < keys.size(); i++){

		//for timestamp
		for (size_t h = 0; h < sizeof(tms)/sizeof(string); h++) {
			//push ip data
			for (size_t j = 0; j < ips.size(); j++) {
				//HSET grp00_t.com.0_1590977400 1.1.1.1 "11|00|33|44|55|66"
				string cmd = "HSET " + keys[i] + tms[h] + " " + ips[j] + " " + vals[h];
				cmds.push_back(cmd);
			}

			//push all data
			//k: grp00_t.com.0_1590977400 all "11|00|33|44|55|66"
			string cmd = "HSET " + keys[i] + tms[h] + " all 99|99|99|99|99|99";
			cmds.push_back(cmd);
		}
	}
}

void redisHelperTestInsertData()
{
	cout << "test redisHelper" << endl;

	HiredisHelper redis_conn;
	string ip = "127.0.0.1";
	int port = 6379;
	string auth_str = "123456";
	int timeout = 200;
	redis_conn.Init(ip, port, auth_str, timeout);

	vector<string> cmds;

	getCmds(cmds, 100, 1000);

	cout << "cmds size:" << cmds.size() << endl;

	fstream fs("./out.log");
	if (!fs) {
		cout << "Error: open file!!!"  << endl;
		exit(1);
	}
	
	clock_t end, start = clock();
	for (size_t i = 0; i < cmds.size(); i++ ) {
		if (i % 1000 == 0) {
			cout << "Complete: " << i << endl;
		}

		fs << cmds[i] << endl;

		redisReply *reply = redis_conn.ExecuteCmd(cmds[i]);
		if (!reply) {
			cout << "Push redis fail i: " << i << " cmd: " << cmds[i] << endl;
			return;
		}
	}

	fs.close();
	end = clock();
	clog << "times: " << " usetime: " << (double)(end - start)/CLOCKS_PER_SEC << "(s)" << endl;
}


