#include <iostream>
#include <string>
#include <vector>

#include "util.h"

using namespace std;

//AVG(ip, total, 5)
//GT(ip_total_5m, 1)
class ExpParse
{
public:
    ExpParse() = default;
    ExpParse(string exp, vector<string> sep);
    ~ExpParse(){};

    friend ostream &operator<<(ostream &output, const ExpParse &b)
    {
        cout << "exp:" << b.exp << endl;
        cout << "funcName:" << b.funcName << endl;
        cout << "field:" << b.field << endl;
        cout << "lastVar:" << b.lastVar << endl;
        for (auto &&i : b.vars)
        {
            cout << "var:" << i << endl;
        }

        for (auto &&i : b.seps)
        {
            cout << "sep:" << i << endl;
        }
        
        return output;
    }

private:
    string exp;
    string funcName;
    string field;
    vector<string> vars;
    vector<string> seps;
    int lastVar;
};
