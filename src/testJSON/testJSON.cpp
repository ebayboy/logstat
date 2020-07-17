/*
    test json
*/
#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include <assert.h>

struct person
{
    std::string name;
    std::string address;
    int age;
};

using namespace nlohmann;
using namespace std;

static void case1()
{
    person p = {"Ned Flanders", "744 Evergreen Terrace", 60};

    // convert to JSON: copy each value into the JSON object
    json j;
    j["name"] = p.name;
    j["address"] = p.address;
    j["age"] = p.age;

    // convert from JSON: copy each value from the JSON object
    person p1{
        j["name"].get<std::string>(),
        j["address"].get<std::string>(),
        j["age"].get<int>()};

    cout << "p1.name:" << p1.name << endl;
    cout << "p1.address:" << p1.address << endl;
    cout << "p1.age:" << p1.age << endl;
}

void to_json(json &j, const person &p)
{
    j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
}

void from_json(const json &j, person &p)
{
    j.at("name").get_to(p.name);
    j.at("address").get_to(p.address);
    j.at("age").get_to(p.age);
}

static void testStruct()
{
    std::cout << __func__ << "=====================" << endl;

    // create a person
    person p{"Ned Flanders", "744 Evergreen Terrace", 60};

    // conversion: person -> json
    // to_json
    json j = p;

    std::cout << j << std::endl;
    // {"address":"744 Evergreen Terrace","age":60,"name":"Ned Flanders"}

    // conversion: json -> person
    // from_json
    auto p1 = j.get<person>();

    // that's it
    cout << "p1.name:" << p1.name << endl;
    cout << "p1.address:" << p1.address << endl;
    cout << "p1.age:" << p1.age << endl;
    //assert(p == p2);
}

int main(int args, char **argv)
{
    case1();
    testStruct();

    return 0;
}
