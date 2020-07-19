/*
    test json
*/
#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

struct person
{
    std::string name;
    std::string address;
    int age;
};

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

static void to_json(json &j, const person &p)
{
    j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
}

static void from_json(const json &j, person &p)
{
    try
    {
        j.at("name").get_to(p.name);
        j.at("address").get_to(p.address);
        j.at("age").get_to(p.age);
    }
    catch (const json::out_of_range &)
    {
    }
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

// ================================= TEST CLASS ===========================================
class CPerson
{
public:
    CPerson(){}; // used by from json
    CPerson(string name, string address, int age)
    {
        this->name = name;
        this->address = address;
        this->age = age;
    }

    friend ostream &operator<<(ostream &output, const CPerson &b)
    {
        output << "name:" << b.name << endl;
        output << "address:" << b.address << endl;
        output << "age:" << b.age << endl;

        return output;
    }

// Person p = json j;
#if 0
    friend void to_json(json &j, const CPerson &p)
    {
        j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
    }
#endif

    //json j = Person{};
    friend void from_json(const json &j, CPerson &p)
    {
        try
        {
            j.at("name").get_to(p.name);
            j.at("address").get_to(p.address);
            j.at("age").get_to(p.age);
        }
        catch (const json::out_of_range &)
        {
        }
    }

private:
    std::string name;
    std::string address;
    int age;
};

static void testClass()
{
    std::cout << __func__ << "=====================" << endl;

#if 0
    // create a person
    CPerson p {"Ned Flanders", "744 Evergreen Terrace", 60};

    // conversion: person -> json
    // to_json
    json j = p;

    std::cout << j << std::endl;
#endif
    //json j = "{\"Ned Flanders\", \"744 Evergreen Terrace\", 60}";
    json j = "{\"address\":\"744 Evergreen Terrace\",\"age\":60,\"name\":\"Ned Flanders\"}"_json;

    // conversion: json -> person
    // from_json
    auto p1 = j.get<CPerson>();

    // that's it
    cout << p1 << endl;
}

int main(int args, char **argv)
{
    case1();
    testStruct();
    testClass();

    return 0;
}
