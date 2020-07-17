#ifndef __UTIL_H__
#define __UTIL_H__
/* code */

#include <string>

int readCfg(std::string filename);
void readargs(int argc, char * const argv[], std::string &c, std::string &d);

#endif //__UTIL_H__
