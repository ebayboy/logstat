
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
using namespace std;


void testJSON()
{
    auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

    std::string s = j3.dump();

    cout << "s:" << s << endl;
}

void readCfg(string filename)
{
    std::ifstream fs(filename);
    json j;
    fs >> j;

    string s = j.dump();

    cout << s << endl;
}

int main(int argc, char const *argv[]) {
    /* code */
    cout << "riskstat start..." << endl;


    readCfg("conf/input.json");

    cout << "riskstat exit!" << endl;

    return 0;
}
