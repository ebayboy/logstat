
#ifndef __TESTREDISHELPER__H_
#define __TESTREDISHELPER__H_

void redisHelperTestInsertData();
void redisHelperPublish();
int hgetallContent(string m_redis_key, vector<string> &items);
int pubStrContent(size_t hostSize);

#endif

