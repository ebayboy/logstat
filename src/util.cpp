
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "util.h"

using json = nlohmann::json;
using namespace std;

int readCfg(std::string filename)
{
    try
    {
        std::ifstream fs(filename);
        if (!fs.is_open()) {
            cerr << "Error: open file failed!" << endl;
            return -1;
        }
        json j;
        fs >> j;
        std::string s = j.dump();
        cout << s << endl;
    }
    catch (std::exception & e)
    {
        cout << "Error: open file!" << e.what() << endl;
    }

    return 0;
}
