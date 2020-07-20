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
    ExpParse e("stat", "AVG(ip, total, 5)");
    cout << "stat:" << e << endl;

    ExpParse e1("risk", "GT(ip_total_5m/all_total_5m,0.1)");

    cout << "e1:" << e1 << endl;

    return 0;
}
