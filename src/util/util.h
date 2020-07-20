#ifndef __UTIL_H__
#define __UTIL_H__
/* code */

#include <string>
#include <vector>

int readCfg(std::string filename);
void readargs(int argc, char * const argv[], std::string &c, std::string &d);
void stringSplit(std::string const s, std::vector<std::string> seps, std::vector<std::string> &strs);

#endif //__UTIL_H__