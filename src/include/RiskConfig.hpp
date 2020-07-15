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

RiskConfig::RiskConfig(std::string cfgName)
{
    nlohmann::json js;
    std::ifstream fs(cfgName);
    if (!fs.bad())
    {
        cerr << "Error: open file failed!" << endl;
    }
    fs >> js;
    std::string s = js.dump();
    cout << s << endl;

    //numstat
    this->numstat = js["numstat"];

    //input array
    RiskInput r;
    auto js_inputs = js["input"];
    for(auto it = js_inputs.begin(); it != js_inputs.end(); it++) {
        cout << *it << endl;
        cout << "111111" << endl;
    }
}

RiskConfig::~RiskConfig()
{
}

#endif // __RISKCONFIG_HPP__
