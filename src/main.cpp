
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;


void testJSON()
{
    auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

    std::string s = j3.dump();

    cout << "s:" << s << endl;
}

int main(int argc, char const *argv[]) {
    /* code */
    cout << "riskstat start..." << endl;


    testJSON();

    cout << "riskstat exit!" << endl;

    return 0;
}
