#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

inline void readargs(int argc, char *const argv[], std::string &c, std::string &d)
{
    int ch;
    while ((ch = getopt(argc, argv, "c:d:v:h")) != -1)
    {
        switch (ch)
        {
        case 'c':
            c = std::string(optarg);
            break;
        case 'v':
            std::cout << "Version: 1.0.0" << std::endl;
            break;
        case 'h':
            std::cout << "Usage: \n\t-c config file\n\t-v version\n"
                      << std::endl;
            break;
        case 'd':
            d = std::string(optarg);
            break;
        }
    }
}

inline void stringSplit(std::string const s, std::string sep, std::vector<std::string> &strs)
{
    std::string::size_type pos = 0, n;

    while (pos != std::string::npos)
    {
        n = s.find(sep, pos);
        if (n == std::string::npos)
        {
            break;
        }
        strs.push_back(s.substr(pos, n - pos));
        pos = n + sep.size();
    }
    strs.push_back(s.substr(pos, s.size() - pos));
}

inline std::vector<string> split(std::string strTime)
{
    std::vector<string> result;
    std::string temp("");
    strTime += ')'; //字符串结束标记，方便将最后一个单词入vector
    for (size_t i = 0; i < strTime.size(); i++)
    {
        if (strTime[i] == '(' || strTime[i] == ')' || strTime[i] == ',' || strTime[i] == '/')
        {
            result.push_back(temp);
            temp = "";
        }
        else
        {
            temp += strTime[i];
        }
    }
    return result;
}

#endif // !__UTIL_HPP__
