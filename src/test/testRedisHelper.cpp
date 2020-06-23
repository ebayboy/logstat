
#include <iostream>
#include <vector>
#include <sstream>

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
static int hgetallContent(HiredisHelper &redis_conn, vector<string> &items) {
    string m_redis_key = "grp00_t.com_1590977640";
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

void redisHelperTest()
{
    cout << "test redisHelper" << endl;

    HiredisHelper redis_conn;
    string ip = "127.0.0.1";
    int port = 6379;
    string auth_str = "123456";
    int timeout = 200;
    redis_conn.Init(ip, port, auth_str, timeout);

    //set string
    int ret = addStrContent(redis_conn);
    if (ret != 0) {
        cout << "reids set failed!" <<endl;
    } else  {
        cout << "reids set ok!" <<endl;
    }

    // get string
    string str;
    ret = getStrContent(redis_conn, str);
    cout << "get str:"  << str << " ret:" << ret << endl;

    //add set 
    ret = addZsetContent(redis_conn);   

    //get set
    vector <string> items;
    ret = getZsetContent(redis_conn, items);
    if (ret == 0) {
        for (unsigned int i = 0; i < items.size(); i++) {
            cout << items[i] << endl;
        }
    }
 
    //hgetall set
    vector <string> hg;
    ret = hgetallContent(redis_conn, hg);
    if (ret == 0) {
        for (unsigned int i = 0; i < hg.size(); i++) {
            cout << hg[i] << endl;
        }
    }
}


