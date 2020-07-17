/*
    test json
*/
#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

struct person
{
    std::string name;
    std::string address;
    int age;
};

using namespace nlohmann;
using namespace std;

int main(int args, char **argv)
{
    person p = {"Ned Flanders", "744 Evergreen Terrace", 60};

    // convert to JSON: copy each value into the JSON object
    json j;
    j["name"] = p.name;
    j["address"] = p.address;
    j["age"] = p.age;

    // convert from JSON: copy each value from the JSON object
    person p1 {
        j["name"].get<std::string>(),
        j["address"].get<std::string>(),
        j["age"].get<int>()};

    cout << "p1.name:" << p1.name << endl;
    cout << "p1.address:" << p1.address << endl;
    cout << "p1.age:" << p1.age << endl;

    return 0;
}
