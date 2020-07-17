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
    RiskConfig(){};
    RiskConfig(int numstat, vector<RiskInput> input){};
    ~RiskConfig(){};

    friend ostream &operator<<(ostream &output, const RiskConfig &b)
    {
        output << "numstat:" << b.numstat << endl;
        output << "sizeof(input):" << b.input.size() << endl;

        for (auto &&i : b.input)
        {
            cout << i << endl;
        }

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

#endif // __RISKCONFIG_HPP__
