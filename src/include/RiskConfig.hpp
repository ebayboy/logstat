#ifndef __RISKCONFIG_HPP__
#define __RISKCONFIG_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "nlohmann/json.hpp"

#include "RiskInput.hpp"
#include "RiskOutput.hpp"
#include "RiskCompute.hpp"

using namespace std;
using namespace nlohmann;

class RiskConfig
{
public:
    friend class RiskInput;
    friend class RiskOnput;
    friend class RiskCompute;

    RiskConfig(){};
    RiskConfig(int numstat, vector<RiskInput> input,
               vector<RiskCompute> stat,
               vector<RiskOutput> output)
        : numstat(numstat), input(input), stat(stat), output(output){};
    ~RiskConfig(){};

    friend ostream &operator<<(ostream &output, const RiskConfig &b)
    {
        output << "numstat:" << b.numstat << endl;
        output << "sizeof(input):" << b.input.size() << endl;
        output << "sizeof(stat):" << b.stat.size() << endl;
        output << "sizeof(output):" << b.output.size() << endl;

        cout << "Input config:" << endl;
        for (auto &&i : b.input)
        {
            cout << i << endl;
        }

        cout << "Stat config:" << endl;
        for (auto &&j : b.stat)
        {
            cout << j << endl;
        }

        cout << "Output config:" << endl;
        for (auto &&k : b.output)
        {
            cout << k << endl;
        }

        return output;
    }

    friend void to_json(json &j, const RiskConfig &p)
    {
        j = json{
            {"numstat", p.numstat},
            {"input", p.input},
            {"stat", p.stat},
            {"output", p.output}};
    }

    friend void from_json(const json &j, RiskConfig &p)
    {
        try {
        j.at("numstat").get_to(p.numstat);
        j.at("input").get_to(p.input);
        j.at("stat").get_to(p.stat);
        j.at("output").get_to(p.output);
        } catch (json::out_of_range &) {

        }
    }

private:
    int numstat;
    vector<RiskInput> input;
    vector<RiskCompute> stat;
    vector<RiskOutput> output;
};

#endif // __RISKCONFIG_HPP__
