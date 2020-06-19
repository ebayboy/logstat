
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
using namespace std;

static int readCfg(string filename)
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
        string s = j.dump();
        cout << s << endl;
    }
    catch (std::exception & e)
    {
        cout << "Error: open file!" << e.what() << endl;
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    /* code */
    cout << "riskstat start..." << endl;

    readCfg("conf/input.json");

    cout << "riskstat exit!" << endl;

    return 0;
}
