#ifndef __RiskCompute_HPP_
#define __RiskCompute_HPP_

#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;
class StatsPolicy
{
public:
    StatsPolicy() = default;
    StatsPolicy(string name, string desc, string expr) : name(name), desc(desc), expr(expr){};
    ~StatsPolicy() = default;

    friend void to_json(nlohmann::json &j, const StatsPolicy &p)
    {
        j = json{
            {"name", p.name},
            {"desc", p.desc},
            {"expr", p.expr}};
    }

    friend void from_json(const nlohmann::json &j, StatsPolicy &p)
    {
        j.at("name").get_to(p.name);
        j.at("desc").get_to(p.desc);
        j.at("expr").get_to(p.expr);
    }

    friend ostream &operator<<(ostream &output, const StatsPolicy &b)
    {
        cout << "name:" << b.name << endl;
        cout << "desc:" << b.desc << endl;
        cout << "expr:" << b.expr << endl;

        return output;
    }

private:
    string name;
    string desc;
    string expr;
};

class RiskCompute
{
public:
    friend class StatsPolicy;
    RiskCompute(){};
    RiskCompute(vector<StatsPolicy> statspolicys) : statspolicys(statspolicys){};
    ~RiskCompute(){};

    friend void to_json(nlohmann::json &j, const RiskCompute &p)
    {
        j = json{{"statspolicys", p.statspolicys}};
    }

    friend void from_json(const nlohmann::json &j, RiskCompute &p)
    {
        j.at("statspolicys").get_to(p.statspolicys);
    }

    friend ostream &operator<<(ostream &output, const RiskCompute &b)
    {

        for (auto &&i : b.statspolicys)
        {
            cout << i << endl;
        }

        return output;
    }

private:
    vector<StatsPolicy> statspolicys;
};

#endif // !__RiskCompute_HPP_