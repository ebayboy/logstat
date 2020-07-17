#ifndef __RISKCONFIG_HPP__
#define __RISKCONFIG_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

#include "RiskInput.hpp"

using namespace std;
using namespace nlohmann;

class RiskConfig
{
public:
    friend class RiskInput;
    RiskConfig() {};
    RiskConfig(string cfgName);
    RiskConfig(int numstat, vector<RiskInput> input){};
    ~RiskConfig();

    friend ostream &operator<<(ostream &output, const RiskConfig &b)
    {
        output << "numstat:" << b.numstat << endl;

        return output;
    }
    friend void to_json(json &j, const RiskConfig &p)
    {
        j = json{
            {"numstat", p.numstat},
            {"input", p.input}};
    }

    friend void from_json(const json &j, RiskConfig &p)
    {
        j.at("numstat").get_to(p.numstat);
        j.at("input").get_to(p.input);
    }

private:
    int numstat;
    vector<RiskInput> input;
};

RiskConfig::RiskConfig(string cfgName)
{
  #if 0 

    auto r = j.get<RiskConfig>();


    auto jinput = j["input"];
    for (auto it = j["input"].begin(); it != jinput.end(); it++)
    {
        //parse input
        cout << "key:" << it.key() << endl;
        cout << "value:" << it.value() << endl;
        cout << "5551111115" << endl;
        RiskInput input{

        };

        this->input.push_back(input);
    }
#endif
}

RiskConfig::~RiskConfig()
{
}

#endif // __RISKCONFIG_HPP__
