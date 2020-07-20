#include <iostream>
#include <string>
#include <vector>

#include "util/util.h"

using namespace std;

//AVG(ip, total, 5)
//GT(ip_total_5m, 1)
class ExpParse
{
public:
    ExpParse() = default;
    ExpParse(string exp, vector<string> sep);
    ~ExpParse(){};

private:
    string exp;
    string field;
    vector<string> vars;
    vector<string> seps;
    int lastVar;
};

