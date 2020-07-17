#ifndef __RISKCONFIG_HPP__
#define __RISKCONFIG_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

#include "RiskInput.hpp"

using namespace std;

class RiskConfig
{
public:
    RiskConfig(string cfgName);
    RiskConfig(RiskConfig &&) = default;
    RiskConfig(const RiskConfig &) = default;
    RiskConfig &operator=(RiskConfig &&) = default;
    RiskConfig &operator=(const RiskConfig &) = default;
    ~RiskConfig();

    int numstat;
    std::vector<RiskInput> inputs;
};

class Student {
    private:
        int age;
        string name;
        string sex;
};

RiskConfig::RiskConfig(std::string cfgName)
{
    nlohmann::json j;
    std::ifstream fs(cfgName);

    cout << "RiskConfig..." << endl;

    if (fs.bad())
    {
        cerr << "Error: open file failed!" << endl;
        return;
    }

    fs >> j;
    //numstat
    cout << "js.dump:" << j.dump() << endl;

    Student s;
    nlohmann::from_json(j, s);


    #if 0
    this->numstat = j["numstat"];
    cout << "numstat:" << this->numstat << endl;

    /*
    namespace ns {
        struct person {
            std::string name;
            std::string address;
            int age;
        };
    }
    ns::person p {
    j["name"].get<std::string>(),
    j["address"].get<std::string>(),
    j["age"].get<int>()
    };
    */
    auto jInputs = j["input"];
    for (auto it = j["input"].begin(); it != jInputs.end(); it++)
    {
        //parse input
        cout << "key:" << it.key() << endl;
        cout << "value:" << it.value() << endl;
        cout << "5551111115" << endl;
        RiskInput input{

        };

        from_json(j["input"], input);

        this->inputs.push_back(input);
    }
    #endif
}

RiskConfig::~RiskConfig()
{
}

#endif // __RISKCONFIG_HPP__
