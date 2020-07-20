/*
    test ExpParse
*/
#include <iostream>
#include <string>
#include <vector>

#include "../ExpParse.hpp"

using namespace std;

int main(int args, char **argv)
{
//ExpParse(string exp, vector<string> seps);
#if 0
    string exp = "AVG(ip, total, 5)";
    ExpParse e("stat", exp);
#else
    string exp = "GT(ip_total_5m/all_total_5m,0.1)";
    ExpParse e("risk", exp);
#endif

    cout << "e:" << e << endl;

    return 0;
}
