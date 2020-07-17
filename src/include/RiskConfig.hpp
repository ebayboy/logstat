#ifndef __RISKCONFIG_HPP__
#define __RISKCONFIG_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

#include "RiskInput.hpp"
#include "RiskCompute.hpp"

using namespace std;
using namespace nlohmann;

class RiskConfig
{
public:
    friend class RiskInput;
    friend class RiskCompute;

    RiskConfig(){};
    RiskConfig(int numstat, vector<RiskInput> input, vector<RiskCompute> stat) : numstat(numstat), input(input), stat(stat){};
    ~RiskConfig(){};

    friend ostream &operator<<(ostream &output, const RiskConfig &b)
    {
        output << "numstat:" << b.numstat << endl;
        output << "sizeof(input):" << b.input.size() << endl;
        output << "sizeof(stat):" << b.stat.size() << endl;

        for (auto &&i : b.input)
        {
            cout << i << endl;
        }

        for (auto &&j : b.stat)
        {
            cout << j << endl;
        }

        return output;
    }

    friend void to_json(json &j, const RiskConfig &p)
    {
        j = json{
            {"numstat", p.numstat},
            {"input", p.input},
            {"stat", p.stat}};
    }

    friend void from_json(const json &j, RiskConfig &p)
    {
        j.at("numstat").get_to(p.numstat);
        j.at("input").get_to(p.input);
        j.at("stat").get_to(p.stat);
    }

private:
    int numstat;
    vector<RiskInput> input;
    vector<RiskCompute> stat;
};

#endif // __RISKCONFIG_HPP__
